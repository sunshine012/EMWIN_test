/*
 * SysDisplay.h
 *
 *  Created on: Jun 18, 2019
 *      Author: che
 */

#ifndef SYSDISPLAY_H_
#define SYSDISPLAY_H_

#include "DrvTypeDefs.h"

#include "DrvLcd_Color320x240.h"


////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////
typedef const CHAR *_DisplayPage[];
typedef _DisplayPage *_DisplayPagePtr;
///////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

// Display options.
#define DISPLAY_NORMAL     0x00
#define DISPLAY_CENTERED   0x01
#define DISPLAY_INVERTED   0x02
#define DISPLAY_UNDERLINED 0x04
#define DISPLAY_FILL       0x08
#define DISPLAY_LINEFEED   0x80
#define DISPLAY_RIGHT      0x10

#define DISPLAY_N          DISPLAY_NORMAL
#define DISPLAY_C          DISPLAY_CENTERED
#define DISPLAY_I          DISPLAY_INVERTED
#define DISPLAY_U          DISPLAY_UNDERLINED
#define DISPLAY_F          DISPLAY_FILL
#define DISPLAY_L          DISPLAY_LINEFEED

#define DISPLAY_CI         (DISPLAY_C | DISPLAY_I)
#define DISPLAY_CU         (DISPLAY_C | DISPLAY_U)
#define DISPLAY_CIF        (DISPLAY_C | DISPLAY_I | DISPLAY_F)
#define DISPLAY_CUF        (DISPLAY_C | DISPLAY_U | DISPLAY_F)

#define DISPLAY_CIL        (DISPLAY_C | DISPLAY_I | DISPLAY_L)
#define DISPLAY_CUL        (DISPLAY_C | DISPLAY_U | DISPLAY_L)
#define DISPLAY_CIFL       (DISPLAY_C | DISPLAY_I | DISPLAY_F | DISPLAY_L)
#define DISPLAY_CUFL       (DISPLAY_C | DISPLAY_U | DISPLAY_F | DISPLAY_L)

typedef enum {
   SYS_DRAW_LINE = DRV_LCD_LOGICAL_OR_DATA,
   SYS_ERASE_LINE = DRV_LCD_LOGICAL_AND_DATA
}_SysLineMode;

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes.
//
////////////////////////////////////////////////////////////////////////////////

void SysDisplaySetCursorAt( UINT16 Row, UINT16 Column );
void SysDisplayFillArea( UINT32 Color, UINT16 StartRow, UINT16 EndRow, UINT16 StartColumn, UINT16 EndColumn );
void SysDisplayClear( UINT8* Device );
void SysDisplayClearLine( UINT16 yc, UINT8 FontHeight );
void SysDisplayRamString( const CHAR* pString, UINT16 Options );



//
////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif /* SYSDISPLAY_H_ */
