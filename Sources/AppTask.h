/*
 * AppTask.h
 *
 *  Created on: May 20, 2019
 *      Author: che
 */

#ifndef APPTASK_H_
#define APPTASK_H_

/***** Required include files *****/
#include "key.h"
#include "Appserial.h"
#include "DrvSpi.h"
#include "DrvSsp.h"
#include "DrvLcd_Color320x240.h"
#include "DrvLcdController_MK70.h"
#include "DrvFlexBus.h"

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

/***** Type definitions *****/


/***** Definitions *****/
//#define	USE_FREERTOS

#define START_TASK_PRIORITY		(tskIDLE_PRIORITY)
#define KEY_TASK_PRIORITY		(tskIDLE_PRIORITY + 2)
#define SERIAL_TASK_PRIORITY	(tskIDLE_PRIORITY + 1)
#define LCD_TASK_PRIORITY		(tskIDLE_PRIORITY + 1)

/***** Macro's *****/

/***** Global variables *****/
extern EventGroupHandle_t xKeyEventGroup;

extern TaskHandle_t	StartTask_Handle;
extern TaskHandle_t	KeyTask_Handle;
extern TaskHandle_t	SerialTask_Handle;
extern TaskHandle_t	LCDTask_Handle;


/***** Function prototypes *****/
void AppStartRTOS(void);

/***** End of include file *****/

#endif /* APPTASK_H_ */
