#ifndef APPDISPLAY_H_
#define APPDISPLAY_H_

/***** Required include files *****/
#include "Dialog.h"
#include <math.h>

/***** Type definitions *****/


/***** Definitions *****/
#define SCREEN_XSIZE		320
#define SCREEN_YSIZE		240

#define ID_WINDOW_0         (GUI_ID_USER + 0x05)

#define PI		(3.141592653)

#define USER_MESSAGE_1  (WM_USER + 1)
/***** Macro's *****/

/***** Global variables *****/

/***** Function prototypes *****/
extern WM_HWIN CreateWindow(void);

/***** End of include file *****/

#endif /* APPSERIAL_H_ */