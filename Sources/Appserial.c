/*
 * Appserial.c
 *
 *  Created on: Apr 15, 2019
 *      Author: che
 */

#include <string.h>
#include "Appserial.h"

void SerialSendData(const void* string)
{
	const AS1_TComData* ptr;
	ptr = (const AS1_TComData*)string;
	while(*ptr != 0)
	{
		while(AS1_SendChar(*ptr) == ERR_TXFULL);
		ptr++;
	}
}

uint8 SerialCheckData(AS1_TComData* dest)
{
	uint8 status = 0;
	EnterCritical();
	
	if((SerialReadIndex != SerialWriteIndex) && RXTimerCounter == 0)
	{
		if(SerialWriteIndex > SerialReadIndex)
		{
			while(SerialReadIndex != SerialWriteIndex)
			{
				*dest++ = SerialRXDataBuf[SerialReadIndex];
				SerialReadIndex++;
			}
		}
		else
		{
			while(SerialReadIndex != SERIAL_RX_DATA_BUF_LENGTH)
			{
				*dest++ = SerialRXDataBuf[SerialReadIndex];
				SerialReadIndex++;
			}
			
			SerialReadIndex = 0;
			while(SerialReadIndex != SerialWriteIndex)
			{
				*dest++ = SerialRXDataBuf[SerialReadIndex];
				SerialReadIndex++;
			}
		}
		status = 1;
	}
	
	ExitCritical();
	return status;
}

void ProcessRXdata(AS1_TComData* src)
{
	if(strncmp((void *)src, "LED_ON", 6) == 0)
	{
		GPIO1_ClearFieldBits(NULL, LED1, 0x01);
	}
	else if(strncmp((void *)src, "LED_OFF", 7) == 0)
	{
		GPIO1_SetFieldValue(NULL, LED1, 0x01);
	}
}

