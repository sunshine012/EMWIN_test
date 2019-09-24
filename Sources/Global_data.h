/*
 * Global_data.h
 *
 *  Created on: Apr 9, 2019
 *      Author: che
 */

#ifndef GLOBAL_DATA_H_
#define GLOBAL_DATA_H_

/***** Required include files *****/
#include "PE_Types.h"
#include "AS1.h"
#include "GUI.h"

/***** Type definitions *****/

/***** Definitions *****/
#define SERIAL_RX_DATA_BUF_LENGTH	128

#define TIMER0_PERIOD_MS			1

#define KEY_SCAN_PERIOD_MS			16

//#define PE_USB

/***** Macro's *****/

/***** Global variables *****/

//extern LDD_TDeviceDataPtr PortC_Device_Data_Ptr;
//extern uint32	PortC_User_Data;

//extern LDD_TDeviceDataPtr PortF_Device_Data_Ptr;
//extern uint32	PortF_User_Data;

//extern LDD_TDeviceDataPtr TimerUnit_Device_Data_Ptr;
//extern uint32	TimerUnit_User_Data;

extern AS1_TComData SerialRXDataBuf[SERIAL_RX_DATA_BUF_LENGTH];
extern uint16 SerialWriteIndex;
extern uint16 SerialReadIndex;

extern uint8 RXTimerCounter;

extern uint8 clockstart;
extern uint16  TimeCounter;
extern uint32  TotalTimeSeconds;

extern LDD_TDeviceData *pDMA_device;
extern LDD_TDeviceData *pUSB_device;


extern volatile GUI_TIMER_TIME OS_TimeMS;

/***** Function prototypes *****/


/***** End of include file *****/

#endif /* GLOBAL_DATA_H_ */
