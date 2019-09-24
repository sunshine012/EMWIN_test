/*
 * AppTask.c
 *
 *  Created on: May 20, 2019
 *      Author: che
 */

#include <string.h>
#include <stdio.h>
#include "GPIO1.h"
#include "GPIO2.h"
#include "Global_data.h"
#include "AppTask.h"
#include "GUI.h"
#include "USB1.h"
#include "USB_PDD.h"

#include "pictures.h"
#include "AppDisplay.h"
#include "psptypes.h"
#include "derivative.h"
#include "hidmouse.h"

void DrvWatchDogDisable(void);
void USBClockInit(void);


#ifdef	USE_FREERTOS
	EventGroupHandle_t xKeyEventGroup;
	TaskHandle_t	StartTask_Handle;
	TaskHandle_t	KeyTask_Handle;
	TaskHandle_t	SerialTask_Handle;
	TaskHandle_t	LCDTask_Handle;

	static void StartTask( void *pvParameters );
	static void KeyTask( void *pvParameters );
	static void SerialTask( void *pvParameters );
	static void LCDTask( void *pvParameters );
#endif

void AppStartRTOS(void)
{
	UINT32 x;
#ifndef LCD_PE_MODE
	DrvSpiInit();
	DrvSspInit(0, 1000000);
#else
	(void)SM1_Init(NULL);
#endif

	(void)TU1_Init(NULL);
	DrvWatchDogDisable();
	
#if PE_USB
	pUSB_device = USB1_Init(NULL);
	USB1_Enable(pUSB_device);
#else
	USBClockInit();
#endif
	

#ifdef	USE_FREERTOS
	xKeyEventGroup = xEventGroupCreate();

	xTaskCreate( StartTask,  "StartTask",  configMINIMAL_STACK_SIZE, NULL, START_TASK_PRIORITY,  &StartTask_Handle );
	vTaskStartScheduler();
#elif PE_USB
	LCDTask(NULL);
#else
	host_main();
#endif
}

void StartTask( void *pvParameters )
{
#ifdef	USE_FREERTOS
	//BaseType_t rlcdTask;
	taskENTER_CRITICAL();

	xTaskCreate( KeyTask,    "KeyTask",    (1024 * 1), 	 					 NULL, KEY_TASK_PRIORITY,    &KeyTask_Handle );
	xTaskCreate( SerialTask, "SerialTask", configMINIMAL_STACK_SIZE, 	 	 NULL, SERIAL_TASK_PRIORITY, &SerialTask_Handle );
	xTaskCreate( LCDTask, 	 "LCDTask",    (1024 * 4), 	 				 	 NULL, LCD_TASK_PRIORITY,	 &LCDTask_Handle );
	vTaskDelete(NULL);

	taskEXIT_CRITICAL();
#endif
}

void KeyTask( void *pvParameters )
{
	//_key key_get;
	EventBits_t rEventBits;
	UINT8 picIndex = 0;
	clockstart = 0;

	for(;;)
	{	
		rEventBits = xEventGroupWaitBits(xKeyEventGroup, (1 << KEY_PRESSED_FLAG_BIT), pdTRUE, pdTRUE, portMAX_DELAY);
		if(rEventBits & ((EventBits_t)(1 << 0)))
		{
		}
		else if(rEventBits & ((EventBits_t)(1 << 1)))	// down key
		{
			//GPIO1_SetFieldValue(NULL, LED1, 0x01);
			GPIO1_ToggleFieldBits(NULL, LED1, 0x01);
			if(picIndex < (PICTURE_NUM - 1))
				picIndex++;
			else
			{
				picIndex = 0;
			}
								
		}
		else if(rEventBits & ((EventBits_t)(1 << 2)))	// up key
		{
			GPIO1_ClearFieldBits(NULL, LED1, 0x01);
			if(picIndex > 0)
				picIndex--;
			else
			{
				picIndex = PICTURE_NUM - 1;
			}
			
		}
		else if(rEventBits & ((EventBits_t)(1 << 3)))	// left key
		{
			if(picIndex > 0)
				picIndex--;
			else
			{
				picIndex = PICTURE_NUM - 1;
			}
		}
		else if(rEventBits & ((EventBits_t)(1 << 4)))	// right key
		{
			if(picIndex < (PICTURE_NUM - 1))
				picIndex++;	
			else
			{
				picIndex = 0;
			}
			
		}
		else if(rEventBits & ((EventBits_t)(1 << 5)))	// enter key
		{
			picIndex = 0;
			clockstart = 1;
			TimeCounter = 0;
			TotalTimeSeconds = 0;
		}
		xTaskNotify(LCDTask_Handle, picIndex, eSetValueWithOverwrite);
		xEventGroupClearBits(xKeyEventGroup, 0xFF);
	}
}

void SerialTask( void *pvParameters )
{
	AS1_TComData RXdatabuf[64];

	for(;;)
	{
		vTaskDelay(pdMS_TO_TICKS(10));
		if(SerialCheckData(RXdatabuf))
		{
			ProcessRXdata(RXdatabuf);
			memset(RXdatabuf, 0x00, 64);
		}
	}
}

void LCDTask( void *pvParameters )
{
#ifdef	USE_FREERTOS
	BaseType_t	rValue;
	UINT32 rNotificationValue;
#endif

	//char *pstring = "Hello NXP emWin!";
	//GUI_DispStringAt(pstring, (SCREEN_XSIZE - GUI_GetStringDistX(pstring))/2, SCREEN_YSIZE/2);
	//UINT8 *paddr;
	
	WM_HWIN hDlg;
	GUI_RECT* pRect;

	GUI_Init();

	hDlg = CreateWindow();
	WM_SelectWindow(hDlg);
	//WM_SendMessageNoPara(hDlg, USER_MESSAGE_1);
	pRect->x0 = 0;
	pRect->y0 = 0;
	pRect->x1 = 1;
	pRect->y1 = 1;
	WM_InvalidateRect(hDlg, pRect);
	WM_Exec();

#ifndef	USE_FREERTOS
	clockstart = 1;
	TimeCounter = 0;
	TotalTimeSeconds = 0;
#endif
	while(1)
	{
		//GUI_X_Delay(20);
		GUI_X_Delay(20);
		myprintf("Test\n");
		myprintf("TotalTimeSeconds = %d\n", TotalTimeSeconds);
		GUI_X_Delay(10);
		myprintf_ok("It is OK\n");
		GUI_X_Delay(10);
		myprintf_error("It is Error\n");
		GUI_X_Delay(10);
		myprintf_info("It is Info\n");
		GUI_X_Delay(10);
		myprintf_isr("It is ISR\n");
		if(DMACH1_GetTransferCompleteStatus(pDMA_device))
		{
			WM_InvalidateRect(hDlg, pRect);
			WM_Exec();
		}
	}

	/*for(;;)
	{
		//rValue = xTaskNotifyWait(0, 0xFFFFFFFF, &rNotificationValue, portMAX_DELAY);
		//if(rValue == pdTRUE)
		//{
			/* paddr = pvPortMalloc(PIC_SIZE_TREE);
			memcpy(paddr, LoadedPics[rNotificationValue].pPicData, LoadedPics[rNotificationValue].PicDataSize);
			GUI_MULTIBUF_BeginEx(0);
			GUI_JPEG_Draw(paddr, LoadedPics[rNotificationValue].PicDataSize, 0, 0);
			GUI_MULTIBUF_EndEx(0);
			vPortFree(paddr);*/
		//}
		/*if(clockstart)
		{




#ifdef	USE_FREERTOS
			vTaskSuspend(NULL);
#else
			GUI_X_Delay(5);
#endif
		}
	}*/
}

void DrvWatchDogDisable(void)
{
	volatile UINT32 delay = 50;

	WDOG_UNLOCK = 0xC520;               //watchdog unlock
   	WDOG_UNLOCK = 0xD928;                                       
                                       //disable watchdog
   	WDOG_STCTRLH &= ~(WDOG_STCTRLH_WDOGEN_MASK);
                                       //needs to be at least 256 bus clock cycles
   	while(delay--);                   //before watchdog registers can be modified again
}  

void USBClockInit(void)
{
	/* Interrupt vector(s) priority setting */
	/* NVICIP73: PRI73=0x80 */
	NVICIP73 = NVIC_IP_PRI73(0x80);
	/* NVICISER2: SETENA|=0x0200 */
	NVICISER2 |= NVIC_ISER_SETENA(0x0200);

	/* SIM_SOPT2: USBFSRC=2,USBF_CLKSEL=1 */
	SIM_SOPT2 = (UINT32)((SIM_SOPT2 & (UINT32)~(UINT32)(
	       SIM_SOPT2_USBFSRC(0x01)
	      )) | (UINT32)(
	       SIM_SOPT2_USBFSRC(0x02) |
	       SIM_SOPT2_USBF_CLKSEL_MASK
	      ));                      /* Clock source=Divided Pll1 clock */

	/* SIM_CLKDIV2: USBFSDIV=4,USBFSFRAC=1 */
	SIM_CLKDIV2 = (UINT32)((SIM_CLKDIV2 & (UINT32)~(UINT32)(
				   SIM_CLKDIV2_USBFSDIV(0x03)
				  )) | (UINT32)(
				   SIM_CLKDIV2_USBFSDIV(0x04) |
				   SIM_CLKDIV2_USBFSFRAC_MASK
				  ));					 /* Div=5 - Mult=2	*/
	
	/* Enable module clock */
	/* SIM_SCGC4: USBFS=1 */
	SIM_SCGC4 |= SIM_SCGC4_USBFS_MASK;	  
	
	/* Reset module */
	/* USB0_USBTRC0: USBRESET=1 */
	USB0_USBTRC0 = USB_USBTRC0_USBRESET_MASK; /* Reset module */
	while (USB_PDD_GetModuleResetPendingFlag(USB0_BASE_PTR)) {
	; /* Wait for reset done */
	}
	/* Enable USB voltage regulator */
	/* SIM_SOPT1: ??=1 */
	SIM_SOPT1 |= 0x80U;                  /* Enable USB voltage regulator */
	/* USB0_USBCTRL: SUSP=1,PDE=0 */
	USB0_USBCTRL = USB_USBCTRL_SUSP_MASK; /* Enable weak pull-downs and suspend transceiver */
	/* USB0_OTGCTL: DPHIGH=0,??=0,DPLOW=1,DMLOW=1,??=0,OTGEN=1,??=0,??=0 */
	USB0_OTGCTL = USB_OTGCTL_DPLOW_MASK |
				  USB_OTGCTL_DMLOW_MASK |
				  USB_OTGCTL_OTGEN_MASK;
}
