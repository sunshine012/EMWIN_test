/*
 * Global_data.c
 *
 *  Created on: Apr 9, 2019
 *      Author: che
 */

#include "Global_data.h"

//LDD_TDeviceDataPtr PortC_Device_Data_Ptr;
//uint32	PortC_User_Data;

//LDD_TDeviceDataPtr PortF_Device_Data_Ptr;
//uint32	PortF_User_Data;

//LDD_TDeviceDataPtr TimerUnit_Device_Data_Ptr;
//uint32	TimerUnit_User_Data;

AS1_TComData SerialRXDataBuf[SERIAL_RX_DATA_BUF_LENGTH];
uint16 SerialWriteIndex;
uint16 SerialReadIndex;

uint8 RXTimerCounter;
uint8 SerialRXStatus;

uint8   clockstart;
uint16  TimeCounter;
uint32  TotalTimeSeconds;

LDD_TDeviceData *pDMA_device;
LDD_TDeviceData *pUSB_device;


