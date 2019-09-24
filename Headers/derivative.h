/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#include "MK70F15.h"

#define _MK_xxx_H_
#define USE_POLL
#define USE_PIT1

#define myprintf myprintf_kinetis
#define smyprintf smyprintf_kinetis

#define ASYNCH_MODE    /* PLL1 is source for MCGCLKOUT and DDR controller */
#define SERIAL_DEBUG

#ifdef SERIAL_DEBUG
#define myprintf	myprintf_kinetis
#define myprintf_ok		DBG_GREEN
#define myprintf_error	DBG_RED
#define myprintf_info		DBG_YELLOW
#define myprintf_isr		DBG_MAGENTA


#define DBG_RED(...)    myprintf("%c[%d;%dm", 0x1B, ATTR_BOLD, FG_RED);           \
                                                myprintf(__VA_ARGS__);                                                            \
                                                myprintf("%c[0m", 0x1B);
#define DBG_GREEN(...)  myprintf("%c[%d;%dm", 0x1B, ATTR_BOLD, FG_GREEN);         \
                                                myprintf(__VA_ARGS__);                                                            \
                                                myprintf("%c[0m", 0x1B);
#define DBG_BLUE(...)   myprintf("%c[%d;%dm", 0x1B, ATTR_BOLD, FG_BLUE);          \
                                                myprintf(__VA_ARGS__);                                                            \
                                                myprintf("%c[0m", 0x1B);
#define DBG_YELLOW(...) myprintf("%c[%d;%dm", 0x1B, ATTR_BOLD, FG_YELLOW);        \
                                                myprintf(__VA_ARGS__);                                                            \
                                                myprintf("%c[0m", 0x1B);
#define DBG_CYAN(...)   myprintf("%c[%d;%dm", 0x1B, ATTR_BOLD, FG_CYAN);          \
                                                myprintf(__VA_ARGS__);                                                            \
                                                myprintf("%c[0m", 0x1B);
#define DBG_MAGENTA(...)myprintf("%c[%d;%dm", 0x1B, ATTR_BOLD, FG_MAGENTA);       \
                                                myprintf(__VA_ARGS__);                                                            \
                                                myprintf("%c[0m", 0x1B);

#define ATTR_RESET		0       // Reset All Attributes (return to normal mode)
#define ATTR_BOLD       1       // Bright (Usually turns on BOLD)
#define ATTR_DIM        2       // Dim
#define ATTR_UNDERLINE  3       // Underline
#define ATTR_BLINK      5       // Blink
#define ATTR_REVERSE    7       // Reverse
#define ATTR_HIDDEN     8       // Hidden

#define FG_BLACK        30
#define FG_RED          31
#define FG_GREEN        32
#define FG_YELLOW       33
#define FG_BLUE         34
#define FG_MAGENTA      35
#define FG_CYAN         36
#define FG_WHITE        37

#define BG_BLACK        40
#define BG_RED          41
#define BG_GREEN        42
#define BG_YELLOW       43
#define BG_BLUE         44
#define BG_MAGENTA      45
#define BG_CYAN         46
#define BG_WHITE        47

#else
#define myprintf
#define myprintf_ok
#define myprintf_error
#define myprintf_info
#define myprintf_isr

#endif
