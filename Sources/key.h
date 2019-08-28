/*
 * key.h
 *
 *  Created on: Apr 11, 2019
 *      Author: che
 */

#ifndef KEY_H_
#define KEY_H_

/***** Required include files *****/
#include <string.h>
#include "PE_Types.h"
#include "Global_data.h"
#include "GPIO2.h"

/***** Type definitions *****/

typedef struct
{
	uint8 key_pressed_num;
	uint8 key_free_flag;
	char  key_value[6];
}_key;

/***** Definitions *****/

#define KEY_COL_NUM	2
#define KEY_ROW_NUM	3
#define KEY_COL0	0
#define KEY_COL1	1
#define KEY_ROW0	0
#define KEY_ROW1	1
#define KEY_ROW2	2

#define KEY_PRESSED_FLAG_BIT	6
#define KEY_FREE_FLAG_BIT		7

#define KEY_SINGLE	0
#define KEY_REPEAT	1

/***** Macro's *****/

/***** Global variables *****/

/***** Function prototypes *****/
void key_scan(void);
_key key_read(uint8 mode);


/***** End of include file *****/

#endif /* KEY_H_ */
