/* ###################################################################
**     Filename    : main.c
**     Project     : PE_Test
**     Processor   : MK70FN1M0VMJ15
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-04-08, 17:17, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "GPIO1.h"
#include "TU1.h"
#include "GPIO2.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "LCDC1.h"
#include "SM1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Global_data.h"
#include "AppTask.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  //_key key_get;
  //AS1_TComData RXdatabuf[64];

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  (void)GPIO1_Init(NULL);
  (void)GPIO2_Init(NULL);
  //DrvFlexBusInit();

  AppStartRTOS();
  
	/*while(1)
	{
		key_get = key_read(KEY_SINGLE);
		if(key_get.key_pressed_num == 1)
		{
			if(strcmp(key_get.key_value, "00") == 0)
			{

			}
			else if(strcmp(key_get.key_value, "01") == 0)
			{
				GPIO1_ClearFieldBits(PortC_Device_Data_Ptr, LED1, 0x01);
			}
			else if(strcmp(key_get.key_value, "02") == 0)
			{
				GPIO1_SetFieldValue(PortC_Device_Data_Ptr, LED1, 0x01);
			}
			else if(strcmp(key_get.key_value, "10") == 0)
			{

			}
			else if(strcmp(key_get.key_value, "11") == 0)
			{

			}
			else if(strcmp(key_get.key_value, "12") == 0)
			{

			}
		}

		if(SerialCheckData(RXdatabuf))
		{
			ProcessRXdata(RXdatabuf);
			memset(RXdatabuf, 0x00, 64);
		}
	}*/
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
