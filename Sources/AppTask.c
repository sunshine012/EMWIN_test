/*
 * AppTask.c
 *
 *  Created on: May 20, 2019
 *      Author: che
 */

#include <string.h>
#include <math.h>
#include <stdio.h>
#include "GPIO1.h"
#include "GPIO2.h"
#include "Global_data.h"
#include "AppTask.h"
#include "SysDisplay.h"
#include "SysFont.h"
#include "DatFont8x16.h"
#include "GUI.h"

#include "pictures.h"
#include "AppDisplay.h"

#define SCREEN_XSIZE		320
#define SCREEN_YSIZE		240


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
#if (configAPPLICATION_ALLOCATED_HEAP == 1)
	uint8_t ucHeap [configTOTAL_HEAP_SIZE] __attribute__ (( section("._D4DRamData_") ));
#endif
#endif

char *itoa_re(int num, char *str, int radix, int strlength);

#ifndef USE_EMWIN
static void display_status(int line, char *title, int status)
{
   SysDisplayClearLine(line, 16);
   SysDisplaySetCursorAt(line, 0);
   SysDisplayRamString(title, DISPLAY_NORMAL);
   SysDisplaySetCursorAt(line, 0);
   if (status) {
	   DrvLcdSetTextColor(COLOR_GREEN);
	   SysDisplayRamString("OK", DISPLAY_RIGHT);
   } else {
	   DrvLcdSetTextColor(COLOR_RED);
	   SysDisplayRamString("!!", DISPLAY_RIGHT);
   }
   DrvLcdSetTextColor(COLOR_WHITE);
}
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

#ifndef USE_EMWIN
	DrvLcdInit( LCD_148_000012, 0, (void*)0x80000000, NULL );
	SysFontHeaderInit(Font8x16, FONT8X16_BYTES_PER_CHAR, FONT8X16_CHAR_COUNT, FONT8X16_CHAR_OFFSET, FONT8X16_HEIGHT, FONT8X16_BLOCK, FONT8X16_UNDERLINE, FONT8X16_WIDTH);
	SysDisplayClear(NULL);
	DrvLcdSetWriteMode(DRV_LCD_LOGICAL_WRITE_DATA);
	display_status(0, "FIRMWARE", 1);
#endif

	(void)TU1_Init(NULL);

#ifdef	USE_FREERTOS
	xKeyEventGroup = xEventGroupCreate();

	xTaskCreate( StartTask,  "StartTask",  configMINIMAL_STACK_SIZE, NULL, START_TASK_PRIORITY,  &StartTask_Handle );
	vTaskStartScheduler();
#else
	LCDTask(NULL);
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

#define PI		(3.141592653)

void LCDTask( void *pvParameters )
{
#ifdef	USE_FREERTOS
	BaseType_t	rValue;
	UINT32 rNotificationValue;
#endif

	//char *pstring = "Hello NXP emWin!";
	//UINT8 *paddr;
	WM_HWIN hDlg;
	int x, y;
	float r;
	float SinTable[60];
	uint8 clock_second, clock_minute, clock_hour, pre_second, pre_minute, pre_hour, daycnt;
	char num_display[12], num_transfer[3];
	GUI_MEMDEV_Handle	hMem;	
	r = 108;
	//GUI_DispStringAt(pstring, (SCREEN_XSIZE - GUI_GetStringDistX(pstring))/2, SCREEN_YSIZE/2);

	GUI_Init();

	hDlg = CreateWindow();
	GUI_SetColor(GUI_WHITE);
	GUI_DrawCircle(SCREEN_XSIZE/2, SCREEN_YSIZE/2, (SCREEN_YSIZE - 10)/2);
	GUI_DrawCircle(SCREEN_XSIZE/2, SCREEN_YSIZE/2, (SCREEN_YSIZE - 10)/2 + 1);
	GUI_DrawCircle(SCREEN_XSIZE/2, SCREEN_YSIZE/2, (SCREEN_YSIZE - 10)/2 + 2);

	for(uint8 i = 0; i < 60; i++)
	{
		SinTable[i] = (float)sin(PI * i / 30);
		x = (int)(r * cos(PI * i / 30));
		y = (int)(r * sin(PI * i / 30));
		if((i % 15) == 0)
		{
			GUI_SetColor(GUI_GREEN);
			GUI_FillCircle(SCREEN_XSIZE/2 + x, SCREEN_YSIZE/2 + y, 4);
		}
		else if((i % 5) == 0)
		{
			GUI_SetColor(GUI_GREEN);
			GUI_FillCircle(SCREEN_XSIZE/2 + x, SCREEN_YSIZE/2 + y, 2);
		}
		else
		{
			GUI_SetColor(GUI_GRAY);
			GUI_FillCircle(SCREEN_XSIZE/2 + x, SCREEN_YSIZE/2 + y, 1);
		}	
	}

	GUI_SetPenSize(1);
	GUI_SetColor(GUI_GRAY);
	GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, SCREEN_XSIZE/2, 20);

	GUI_SetPenSize(3);
	GUI_SetColor(GUI_BLUE);
	GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, SCREEN_XSIZE/2, 30);

	GUI_SetPenSize(3);
	GUI_SetColor(GUI_GREEN);
	GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, SCREEN_XSIZE/2, 40);

#ifndef	USE_FREERTOS
	clockstart = 1;
	TimeCounter = 0;
	TotalTimeSeconds = 0;
#endif
	while(1)
	{
		GUI_X_Delay(1);
	}

	for(;;)
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
		if(clockstart)
		{
			pre_second = clock_second;
			pre_minute = clock_minute;
			pre_hour = clock_hour;
			clock_second = (uint8)(TotalTimeSeconds % 60);
			clock_minute = (uint8)((TotalTimeSeconds / 60) % 60);
			clock_hour   = (uint8)(((TotalTimeSeconds / 60) / 60) % 12);
			daycnt = (uint8)(TotalTimeSeconds / 86400);

			GUI_MULTIBUF_BeginEx(0);
			//GUI_Clear();
			// second
			GUI_SetPenSize(1);
			r = SCREEN_YSIZE/2 - 20;
			x = SCREEN_XSIZE/2 + (int)(r * SinTable[pre_second]);
			y = SCREEN_YSIZE/2 - (int)(r * SinTable[(pre_second + 15)%60]);
			GUI_SetColor(GUI_BLACK);
			GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, x, y);

			GUI_SetColor(GUI_GRAY);
			x = SCREEN_XSIZE/2 + (int)(r * SinTable[clock_second]);
			y = SCREEN_YSIZE/2 - (int)(r * SinTable[(clock_second + 15)%60]);
			GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, x, y);

			// minute
			GUI_SetPenSize(3);
			r = SCREEN_YSIZE/2 - 30;
			if(pre_minute != clock_minute)
			{
				x = SCREEN_XSIZE/2 + (int)(r * SinTable[pre_minute]);
				y = SCREEN_YSIZE/2 - (int)(r * SinTable[(pre_minute + 15)%60]);				
				GUI_SetColor(GUI_BLACK);
				GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, x, y);
			}
			x = SCREEN_XSIZE/2 + (int)(r * SinTable[clock_minute]);
			y = SCREEN_YSIZE/2 - (int)(r * SinTable[(clock_minute + 15)%60]);			
			GUI_SetColor(GUI_BLUE);
			GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, x, y);

			// Hour
			GUI_SetPenSize(3);
			r = SCREEN_YSIZE/2 - 40;
			if((pre_hour + pre_minute / 12) != (clock_hour + clock_minute / 12))
			{
				x = SCREEN_XSIZE/2 + (int)(r * SinTable[pre_hour * 5 + pre_minute/12]);
				y = SCREEN_YSIZE/2 - (int)(r * SinTable[((pre_hour * 5 + pre_minute/12 + 15) % 60)]);				
				GUI_SetColor(GUI_BLACK);
				GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, x, y);
			}
			x = SCREEN_XSIZE/2 + (int)(r * SinTable[clock_hour * 5 + clock_minute/12]);
			y = SCREEN_YSIZE/2 - (int)(r * SinTable[((clock_hour * 5 + clock_minute/12 + 15) % 60)]);			
			GUI_SetColor(GUI_GREEN);
			GUI_DrawLine(SCREEN_XSIZE/2, SCREEN_YSIZE/2, x, y);

			memset(num_display, 0, 12);
			// day
			itoa_re(daycnt, num_transfer, 10, 2);
			strncpy(num_display, num_transfer, 2);
			strcat(num_display, ":");
			// hour
			itoa_re(clock_hour, num_transfer, 10, 2);
			strncpy(num_display + 3, num_transfer, 2);
			strcat(num_display, ":");
			// minute
			itoa_re(clock_minute, num_transfer, 10, 2);
			strncpy(num_display + 6, num_transfer, 2);
			strcat(num_display, ":");
			// second
			itoa_re(clock_second, num_transfer, 10, 2);
			strncpy(num_display + 9, num_transfer, 2);	

			GUI_SetColor(GUI_WHITE);	
			GUI_DispStringAt(num_display, (SCREEN_XSIZE - GUI_GetStringDistX(num_display))/2, SCREEN_YSIZE/2 + 16);	
			GUI_MULTIBUF_EndEx(0);

#ifdef	USE_FREERTOS
			vTaskSuspend(NULL);
#else
			GUI_X_Delay(1);
#endif
		}
	}
}

char *itoa_re(int num, char *str, int radix, int strlength)
{
    char* ptr = str;
	char* ptemp;
    int i;
    int j;
	int orilen;
	if(num == 0)
	{
		for(i = 0; i < strlength; i++)
			str[i] = '0';
		return str;
	}
    while (num)
    {
        *ptr++  = num % radix + '0';
        num    /= radix;
        if (num < radix)
        {
            *ptr++  = num + '0';
            *ptr    = '\0';
            break;
        }
    }
    j = ptr - str - 1;
    for (i = 0; i < (ptr - str) / 2; i++)
    {
        int temp = str[i];
        str[i]  = str[j];
        str[j--] = temp;
    }

	orilen = strlen(str);
	if(orilen < strlength)
	{
		strcpy(ptemp, str);
		for(i = 0; i < (strlength - orilen); i++)
			str[i] = '0';
		strcat(str + i, ptemp);
		str[strlength] = '\0';
	}

    return str;
}
