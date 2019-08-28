/*
 * key.c
 *
 *  Created on: Apr 11, 2019
 *      Author: che
 */

#include "key.h"
#include "AppTask.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "event_groups.h"

static _key	key_save;


void key_scan(void)
{
#ifdef USE_FREERTOS
	 EventBits_t bitstoSet;
	 BaseType_t xHigherPriorityTaskWoken, xResult;	
#endif	 
	 //static uint8  key_counter[KEY_COL_NUM][KEY_ROW_NUM] = {{0}, {0}};
	 GPIO2_TFieldValue row_value;
	 //uint8 key_sum;
	 static uint8 key_column;
	 
	// Toggle the column line status every period
	GPIO2_ToggleFieldBits(NULL, KEY_COLOUM, (GPIO2_TFieldValue)(0x0003));
	
	// check the row line status every period
#ifdef USE_FREERTOS
	bitstoSet = 0;
#endif

	row_value = GPIO2_GetFieldValue(NULL, KEY_ROWS);
	if(row_value != 0x07)	// there is key pressed
	{
		if(((GPIO_PDD_GetPortDataOutput(GPIO2_MODULE_BASE_ADDRESS) >> 8) & 0x03) == 0x02)	//	COL 0
		{
			for(uint8 i = 0; i < KEY_ROW_NUM; i++)
			{
				if((row_value & (0x01 << i)) == 0)
				{
					//(key_counter[KEY_COL0][i] >= 3) ? (key_counter[KEY_COL0][i] = 3) : (key_counter[KEY_COL0][i]++);
					//key_counter[KEY_COL0][i] = 1;
#ifdef USE_FREERTOS					
					bitstoSet |= (1 << i);
#endif					
					key_column = 0;
				}
				//else
				//	key_counter[KEY_COL0][i] = 0;
			}
		}
		else	// COL 1
		{
			for(uint8 i = 0; i < KEY_ROW_NUM; i++)
			{
				if((row_value & (0x01 << i)) == 0)
				{
					//(key_counter[KEY_COL1][i] >= 3) ? (key_counter[KEY_COL1][i] = 3) : (key_counter[KEY_COL1][i]++);
					//key_counter[KEY_COL1][i] = 1;
#ifdef USE_FREERTOS					
					bitstoSet |= (1 << (KEY_ROW_NUM + i));
#endif					
					key_column = 1;
				}
				//else
				//	key_counter[KEY_COL1][i] = 0;
			}
		}

		/*for(uint8 j = 0; j < KEY_COL_NUM; j++)
			for(uint8 k = 0; k < KEY_ROW_NUM; k++)
			{
				if(key_counter[j][k] == 3)
				{*/
					/*if(key_save.key_pressed_num == 1)
						key_save.key_free_flag = 1;
						
					key_save.key_pressed_num++;
					strcat(key_save.key_value, key_value_string[j * KEY_ROW_NUM + k]);

					if(key_save.key_pressed_num >= 2)
						break;*/
					/* bitstoSet |= (1 << (j * KEY_ROW_NUM + k));
				}
			}
		*/
#ifdef USE_FREERTOS
		xResult = xEventGroupGetBitsFromISR(xKeyEventGroup);
		if(xResult & (1 << KEY_FREE_FLAG_BIT))
		{
			bitstoSet &= ~((EventBits_t)(1 << KEY_FREE_FLAG_BIT));
			bitstoSet |= (1 << KEY_PRESSED_FLAG_BIT);
			xResult = xEventGroupSetBitsFromISR(xKeyEventGroup, bitstoSet, &xHigherPriorityTaskWoken);
			
			if(xResult != pdFAIL)
			{
				portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
			}
		}
#endif		
	}
	else
	{
		/*if(((GPIO_PDD_GetPortDataOutput(GPIO2_MODULE_BASE_ADDRESS) >> 8) & 0x03) == 0x02)	// COL 0
			memset(key_counter[KEY_COL0], 0x00, sizeof(key_counter)/KEY_COL_NUM);
		else
			memset(key_counter[KEY_COL1], 0x00, sizeof(key_counter)/KEY_COL_NUM);

		key_sum = 0;
		for(uint8 j = 0; j < KEY_COL_NUM; j++)
			for(uint8 k = 0; k < KEY_ROW_NUM; k++)
				key_sum += key_counter[j][k];*/
		if(((key_column == 0) && (((GPIO_PDD_GetPortDataOutput(GPIO2_MODULE_BASE_ADDRESS) >> 8) & 0x03) == 0x02)) ||
		   ((key_column == 1) && (((GPIO_PDD_GetPortDataOutput(GPIO2_MODULE_BASE_ADDRESS) >> 8) & 0x03) == 0x01)))
		{
#ifdef USE_FREERTOS			
			bitstoSet = (1 << KEY_FREE_FLAG_BIT);
			xResult = xEventGroupSetBitsFromISR(xKeyEventGroup, bitstoSet, &xHigherPriorityTaskWoken);
			
			if(xResult != pdFAIL)
			{
				portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
			}
#endif			
		}
				
		/*if(key_sum == 0)
		{
			//key_save.key_pressed_num = 0;
			//key_save.key_free_flag = 1;
			bitstoSet = (1 << KEY_FREE_FLAG_BIT);
			xResult = xEventGroupSetBitsFromISR(xKeyEventGroup, bitstoSet, &xHigherPriorityTaskWoken);
			
			if(xResult != pdFAIL)
			{
				portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
			}
		}*/
	}
}

_key key_read(uint8 mode)
{
	_key key_refresh;
	
	if(mode)
		key_save.key_free_flag = 1;

	if(key_save.key_free_flag)
	{
		key_save.key_free_flag = 0;
		return (key_save);
	}
	else
	{
		key_refresh.key_pressed_num	= 0;
		return (key_refresh);
	}
}

