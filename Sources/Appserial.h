/*
 * Appserial.h
 *
 *  Created on: Apr 15, 2019
 *      Author: che
 */

#ifndef APPSERIAL_H_
#define APPSERIAL_H_

/***** Required include files *****/
#include "AS1.h"
#include "GPIO1.h"
#include "Global_data.h"

/***** Type definitions *****/


/***** Definitions *****/



/***** Macro's *****/

/***** Global variables *****/

/***** Function prototypes *****/
uint8 SerialCheckData(AS1_TComData* dest);
void ProcessRXdata(AS1_TComData* src);

/***** End of include file *****/

#endif /* APPSERIAL_H_ */
