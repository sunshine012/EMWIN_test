/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.24 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  NXP Semiconductors USA, Inc.  whose
registered  office  is  situated  at 411 E. Plumeria Drive, San  Jose,
CA 95134, USA  solely for  the  purposes  of  creating  libraries  for
NXPs M0, M3/M4 and  ARM7/9 processor-based  devices,  sublicensed  and
distributed under the terms and conditions of the NXP End User License
Agreement.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIConf.c
Purpose     : Display controller initialization
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "LCDConf.h"
#include <string.h>

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Define the available number of bytes available for the GUI
//

#define USE_DDR_BUFFER

#ifdef USE_DDR_BUFFER
    #define GUI_NUMBYTES  (1024 * 1024 * 2)
    // the address by manual
    #define LCD_GUI_RAM_BASE  (LCD_VRAM_BASE_ADDR + (1024 * 1024 * 4))
#else    
    #define GUI_NUMBYTES  (1024 * 32)
#endif

// Define the average block size
#define GUI_BLOCK_SIZE  (0x40)



/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   available memory for the GUI.
*/
void GUI_X_Config(void) {
//
// 32 bit aligned memory area
//
#ifndef  USE_DDR_BUFFER
    static U32 aMemory[GUI_NUMBYTES / 4];
#endif    
//
// Assign memory to emWin
//
#ifdef  USE_DDR_BUFFER
    GUI_ALLOC_AssignMemory((void *)LCD_GUI_RAM_BASE, GUI_NUMBYTES);
#else
    GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);
#endif

GUI_ALLOC_SetAvBlockSize(GUI_BLOCK_SIZE);
//
// Set default font
//
GUI_SetDefaultFont(GUI_FONT_8X16);
}

/*************************** End of file ****************************/
