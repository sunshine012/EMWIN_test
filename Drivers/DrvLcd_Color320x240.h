
/**
 * @file   DrvLcd_Color320x240.h
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Definitions for LCD
 *
 * Contains the LCD definitions
 */

#ifndef _DRV_LCD_COLOR320X240_H_
#define _DRV_LCD_COLOR320X240_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvTypeDefs.h"
#include "DrvIOPort.h"
#include "IO_Map.h"

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

typedef enum{
	DRV_LCD_LOGICAL_OR_DATA = 0,
	DRV_LCD_LOGICAL_AND_DATA = 1,
	DRV_LCD_LOGICAL_XOR_DATA = 2,
	DRV_LCD_LOGICAL_WRITE_DATA = 3
}_DrvLcdDataMode;

#define LCD_RS_COMMAND           0                          //!< LCD command mode
#define LCD_RS_DATA              1                          //!< LCD data mode

//
// IO lines.
//

// Data register.
#define LcdDataPort              (*(volatile UINT8*)0x00200001)    //!< LCD Data Address
#define LcdCommandPort           (*(volatile UINT8*)0x00200000)    //!< LCD Command Address


#define LCD_CURSOR_MODE_OFF         0                       //!< cursor off
#define LCD_CURSOR_MODE_OR          1                       //!< cursor ored with background
#define LCD_CURSOR_MODE_XOR         2                       //!< cursor xored with background
#define LCD_CURSOR_MODE_AND         3                       //!< cursor anded with background
#define LCD_CURSOR_OP_ARITH_OFF     0                       //!< cursor logic off
#define LCD_CURSOR_OP_ARITH_ON      1                       //!< cursor logic on
#define LCD_CURSOR_BLINK_OFF        0                       //!< cursor blink off
#define LCD_CURSOR_BLINK_ON         1                       //!< cursor blink on

#define LCD_MAX_PALLET_ENTRIES      256                     //!< LCD maximum pallet entries

#define LCD_ROW_HEIGHT              8                       //!< LCD row height

#define LCD_CONTRAST_MIN            0                       //!< LCD contrast minimum
#define LCD_CONTRAST_MAX            63                      //!< LCD contrast maximum
#define LCD_CONTRAST_DEFAULT        31                      //!< LCD contrast default

#define LCD_MID_184_310             0x1234567              //!< LCD part number 184-310
#define LCD_ES13BA0FLY              0x0E13BA0F              //!< LCD part number ES13BA0FLY
#define LCD_148_000012              0xFFFFFFFF              //!< LCD part number 148-000012


#define FLCD_CLK                    5000000                 //!< LCD clock 5MHz

#define LCD_BRIGHTNESS_IO_BIT       16                      //!< LCD bright I/O bit number


typedef enum LcdColor
{
   COLOR_WHITE = 0x00FFFFFF,     
   COLOR_DARK_RED = 0x00FF0000,  
   COLOR_DARK_GREEN = 0x0000FF00,
   COLOR_DARK_YELLOW = 0x00FFFF00,    
   COLOR_DARK_BLUE = 0x000000FF, 
   COLOR_DARK_CYAN = 0x0000FFFF,   
   COLOR_DARK_MAGENTA = 0x00FF00FF,      
   COLOR_LITE_GRAY = 0x00808080, 
   COLOR_GREEN = 0x0000FF00,
   COLOR_BLUE = 0x000000FF,
   COLOR_RED = 0x00FF0000,
   COLOR_ORANGE = 0x00888800,
   COLOR_YELLOW = 0x00FFFF00,
   COLOR_CYAN = 0x0000FFFF,
   COLOR_DARK_GRAY = 0x00AAAAAA,
   COLOR_PURPLE = 0x00FFFF80,
   COLOR_LIGHT_BLUE = 0x00000080,   
   COLOR_OFF_WHITE = 0x00101010,
   COLOR_BLACK = 0x00000000
}_LcdColor, *_LCDColor;

typedef enum
{
   DIM_BRIGHTNESS = 0,
   MAX_BRIGHTNESS = 1
}_LcdBackLightLevel;

typedef union ColorTableStruct{
   UINT32   Reg;
   struct{
      UINT32   Blue:8;
      UINT32   Green:8;
      UINT32   Red:8;
      UINT32   NotUsed:8;
   }RGB;
}_ColorTable;
   
typedef struct LcdPalletStruct{
   UINT32         PalletID;               //!< Pallet Id
   UINT32         NumberEntriesUsed;      //!< set equal to 2^^BPP, where BPP is bits per pixel
                                          //!< pallet table entries
   _ColorTable*   pColorTable;            
}_LcdPallet;

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

//#define DrvBackLightBright()        DrvWriteMemoryMappedIO(&MM_OUTPUT_PORT_1, (DrvReadMemoryMappedIO(&MM_OUTPUT_PORT_1) | (0x01 << LCD_BRIGHTNESS_IO_BIT)))
//#define DrvBackLightDim()           DrvWriteMemoryMappedIO(&MM_OUTPUT_PORT_1, (DrvReadMemoryMappedIO(&MM_OUTPUT_PORT_1) & ~(0x01 << LCD_BRIGHTNESS_IO_BIT)))

////////////////////////////////////////////////////////////////////////////////
//
// External declarations.
//
////////////////////////////////////////////////////////////////////////////////

extern UINT16 LcdCurrentLine;
extern UINT16 LcdCurrentRow;
extern UINT16 LcdCurrentColumn;

////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes.
//
////////////////////////////////////////////////////////////////////////////////

const CHAR* DrvLcdDisplayGetVersion(void);
void DrvLcdWritePixel( UINT16 Row, UINT16 Column, UINT32 Color);
UINT32 DrvLcdReadPixel(UINT16 Row, UINT16 Column);
void DrvLcdAutoIncrementAddress(void);
_LcdColor DrvLcdSetPenColor( _LcdColor Color );
_LcdColor DrvLcdGetPenColor( void );
_LcdColor DrvLcdSetBrushColor( _LcdColor Color );
_LcdColor DrvLcdGetBrushColor( void );
_LcdColor DrvLcdSetBackgroundColor( _LcdColor Color );
_LcdColor DrvLcdGetBackgroundColor( void );
_LcdColor DrvLcdSetTextColor( _LcdColor Color );
_LcdColor DrvLcdGetTextColor( void );
UINT8 DrvLcdSetAutoIncrementMode(UINT8 Mode);
UINT8 DrvLcdGetAutoIncrementMode( void );
void DrvLcdSetFrameAddress(void* Address);
void* DrvLcdGetFrameAddress(void);
void DrvLcdSetCurrentDisplayFrame(void* Address);
void* DrvLcdGetCurrentDisplayFrame(void);
void DrvLcdPalletInit( const _LcdPallet* Pallet, volatile UINT32* LcdPalletRam );
void DrvLcdInit( UINT32 LCDPartNumber, UINT32 LcdController, void* FrameAddress, const _LcdPallet* PalletAddress );
void DrvLcdSetModifyRead( void );
void DrvLcdResetModifyRead( void );
volatile UINT8 DrvLcdReadStatus( UINT8 Mask );
void DrvLcdReadWriteData(UINT32 Data, UINT8 Mask);
volatile UINT8 DrvLcdDummyReadData( void );
volatile UINT32 DrvLcdReadData( void );
void DrvLcdWriteData( UINT32 Data );
void DrvSetContrast( UINT8 Contrast, UINT32 LCDPartNumber );
void DrvLcdBackLight( UINT8 Mode );
void DrvLcdWriteFrame( UINT16 Row, UINT16 Column, UINT32 Color );
void DrvLcdCls( void );
void DrvLcdFill( BOOL Mode );
void DrvLcdLineFeed( UINT8 FontHeight );
void DrvLcdSetCursorAt( UINT16 Row, UINT16 Column );
void DrvLcdSetDisplayOrigin(UINT16 x, UINT16 y);
void DrvLcdSetRowAt( UINT16 Row );
void DrvLcdSetColumnAt( UINT16 Column );
void DrvLcdDisplayGraphic( const void* Data, UINT16 Width, UINT16 Height, UINT16 ColorMode );
_DrvLcdDataMode DrvLcdSetWriteMode( _DrvLcdDataMode Mode );
void DrvLcdClearLine( UINT16 Line );
void DrvLcdFillLine( UINT8 Pattern );
void DrvLcdClearLines( UINT16 First, UINT16 Last );
void DrvBacklightLevelSelect(_LcdBackLightLevel Level);
//
// End of include file.
//

#endif





