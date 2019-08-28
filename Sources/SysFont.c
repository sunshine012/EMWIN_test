/*******************************************************************************
 *
 * Platform:      184-966
 * Module:        System
 * File:          SysFont.c
 *
 * Designed by:   Kees Hemmes
 *
 * $Workfile: SysFont.c $
 * $Archive: /EECS750/317 PCB/192-160070 Bootloader/Sources/System/SysFont.c $
 * $History: SysFont.c $
 * 
 * *****************  Version 1  *****************
 * User: Akoscielak   Date: 7/10/14    Time: 10:00a
 * Created in $/EECS750/317 PCB/192-160070 Bootloader/Sources/System
 * 
 * Description:
 * 
 * References:
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "SysFont.h"


////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////

_FontHeader    FontHeader;

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

void SysFontHeaderInit(DATA_PTR address, UINT8 bytesPerChar, UINT8 charcount, UINT8 charoffset, UINT8 Height, UINT8 invertchar, UINT8 underline, UINT8 width)
{
	FontHeader.Address = address;
	FontHeader.BytesPerChar = bytesPerChar;
	FontHeader.CharCount = charcount;
	FontHeader.CharOffset = charoffset;
	FontHeader.Height = Height;
	FontHeader.InvertChar = invertchar;
	FontHeader.Underline = underline;
	FontHeader.Width = width;
}

UINT8 SysFontGetCharData( CHAR Char, void *Buffer, UINT8 *Height )
{
   if( (UINT8)Char < FontHeader.CharOffset )
   {
      Char = 0;
   }
   else
   {
      Char = (UINT8)Char - FontHeader.CharOffset;
   }

   memcpy( Buffer, ((UINT8*)FontHeader.Address + ((UINT16)Char * FontHeader.BytesPerChar)), 
             FontHeader.BytesPerChar );


   *Height = FontHeader.Height;

   return( FontHeader.Width );
}

void SysFontGetCharLineData( CHAR NChar, UINT16 Line, void *Buffer )
{
   UINT16   WChar;
   UINT16   Width;

   WChar = (UINT16)NChar & 0x00FF;
   
   if( WChar < (UINT16)FontHeader.CharOffset )
   {
      WChar = 0;
   }
   else
   {
      WChar = WChar - (UINT16)FontHeader.CharOffset;
   }
   Width = ((FontHeader.Width + 7) / 8);

	memcpy( Buffer, ((UINT8*)FontHeader.Address + 
	    (((UINT16)WChar * FontHeader.BytesPerChar) + ((UINT16)Line * Width))), Width );
}

UINT8 SysFontGetStringWidth( const CHAR *String )
{
   return( strlen( String ) * FontHeader.Width );
}

UINT8 SysGetFontWidth( void )
{
   return( FontHeader.Width );
}

UINT8 SysGetFontHeight( void )
{
   return( FontHeader.Height );
}


