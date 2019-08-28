/*
 * SysDisplay.c
 *
 *  Created on: Jun 18, 2019
 *      Author: che
 */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "SysDisplay.h"
#include "SysFont.h"
#include "DrvLcdController_MK70.h"

UINT16   StartRow;

 void SysDisplaySetCursorAt( UINT16 Row, UINT16 Column )
{
   DrvLcdSetCursorAt( Row, Column );
}

void SysDisplayFillArea( UINT32 Color, UINT16 StartRow, UINT16 EndRow, UINT16 StartColumn, UINT16 EndColumn )
{
   UINT16   Row;
   UINT16   Column;

   for( Row = StartRow; (Row < EndRow && Row < LCD_SCREEN_HEIGHT); Row++ )
   {
      DrvLcdSetCursorAt( Row, StartColumn );
      
      for( Column = StartColumn; Column <= EndColumn && Column < LCD_SCREEN_WIDTH; Column++ ) 
      {
         DrvLcdWritePixel(Row, Column, Color);
      }
   }
   DrvLcdSetCursorAt( StartRow, StartColumn );
}

 void SysDisplayClear( UINT8* Device )
 {
	DrvLcdCls();
 }

 void SysDisplayClearLine( UINT16 yc, UINT8 FontHeight )
{
	SysDisplaySetCursorAt( yc, 0 );
	SysDisplayFillArea( DrvLcdGetBackgroundColor(), yc, yc + FontHeight, 0, LCD_SCREEN_WIDTH );
	SysDisplaySetCursorAt( yc, 0 );
}

void DisplayCharLine( CHAR Char, UINT16 Row, UINT8 Options )
{	
	UINT8		LineBuffer[ FONT_MAX_CHAR_WIDTH / 8 ];
	_LcdColor	color;
	UINT16		width;
	UINT16		FontWidth;
	UINT16		Index;
	UINT8		Mask;

	SysFontGetCharLineData( Char, (Row - StartRow), LineBuffer );
	color = DrvLcdGetTextColor();
	FontWidth = SysGetFontWidth();

	if( Options & DISPLAY_UNDERLINED )
	{
		for( Index = 0; Index < FontWidth; Index += 8 )
		{
		  LineBuffer[Index / 8] = 0xFF;
		}
	}

	if( Options & DISPLAY_INVERTED )
	{
		color ^= 0x00FFFFFF;
	}

	for(width = 0, Mask = 0; width < FontWidth; width++)
	{
		if(Mask == 0)
		  Mask = 0x80;
		if(LineBuffer[width / 8] & (Mask >> (width % 8)))
		{
		  DrvLcdWriteData(color);
		}
		else
		{
		  DrvLcdAutoIncrementAddress();
		}
	}
}

 void  SysDisplayRamString( const CHAR* pString, UINT16 Options )
 { 
   UINT16 Column;
   UINT16 LineOptions = DISPLAY_NORMAL;
   UINT16 LastRow;
   UINT16 Row;
   UINT16 Index;

   Column = LcdCurrentColumn;

   LastRow = SysGetFontHeight() + LcdCurrentRow;
   for( Row = LcdCurrentRow, StartRow = LcdCurrentRow; Row < LastRow; Row++ )
   {
      if( Row < LastRow - 1 )
      {
         LineOptions = Options & ~DISPLAY_UNDERLINED;
      }
      else
      {
         LineOptions = Options;
      }

      if( Options & DISPLAY_CENTERED )
      {
         DrvLcdSetCursorAt(Row, (LCD_SCREEN_WIDTH - SysFontGetStringWidth( pString )) / 2);
      }
      else if (Options & DISPLAY_RIGHT) {
         DrvLcdSetCursorAt(Row, LCD_SCREEN_WIDTH - SysFontGetStringWidth(pString));
      } else
      {
         DrvLcdSetCursorAt(Row, Column);
      }

      // Print the current font line for the string.
      for( Index = 0; pString[ Index ]; Index++ )
      {
         DisplayCharLine( toupper(pString[Index]), Row, LineOptions );
      }
   }

   if( (LineOptions & DISPLAY_LINEFEED) )
   {
      DrvLcdSetCursorAt( StartRow + SysGetFontHeight(), 0 );
   }
   else
      DrvLcdSetCursorAt( StartRow, LcdCurrentColumn );
}
