
/**
 * @file   DrvLcd_Color320x240.c
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Driver for the LCD.
 *
 * This file implements the driver functions for the LCD
 */

//
// Required include files.
//
#include "DrvTypeDefs.h"
//#include "DrvCpu.h"
//#include "DrvPit.h"

#include "DrvSpi.h"
#include "DrvSsp.h"
#include "DrvIOPort.h"
#include "DrvLcdController_MK70.h"
#include "DrvLcd_Color320x240.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

UINT8             LcdContrast;         //!< Current LCD contrast
UINT16            LcdCurrentLine;      //!< Current LCD line 
UINT16            LcdCurrentRow;       //!< Current LCD row
UINT16            LcdCurrentColumn;    //!< Current LCD column
UINT32            LcdBackgroundColor;  //!< Current LCD background color
UINT32            LcdTextColor;        //!< Current LCD text color
UINT32            LcdPenColor;         //!< Current LCD pen color
UINT32            LcdBrushColor;       //!< Current LCD brush color

                                       //! Current address increment mode
UINT8             LcdAddressAutoIncrement;
void*             LcdFrameAddress;     //!< Current LCD frame address
_DrvLcdDataMode   LcdWriteMode;        //!< Current LCD write mode

_ColorTable DefaultColorTable[] = {    //!< Default color pallet
{COLOR_WHITE},
{COLOR_DARK_RED},
{COLOR_DARK_GREEN},
{COLOR_DARK_YELLOW}, 
{COLOR_DARK_BLUE}, 
{COLOR_DARK_CYAN}, 
{COLOR_DARK_MAGENTA},
{COLOR_LITE_GRAY}, 
{COLOR_GREEN},
{COLOR_BLUE},
{COLOR_RED},
{COLOR_ORANGE},
{COLOR_YELLOW},
{COLOR_CYAN},
{COLOR_DARK_GRAY},
{COLOR_PURPLE},
{COLOR_LIGHT_BLUE},
{COLOR_OFF_WHITE},
{COLOR_BLACK}
};

_LcdPallet DefaultPallet = {        //!< Default color pallet
   0,
   19,
   (_ColorTable*)&DefaultColorTable
};

#if (DRV_LIB_REV == 1000)
const CHAR DrvLcdDisplayVersion[] = "1.0.0.0";
#else
const CHAR DrvLcdDisplayVersion[] = "2.0.0.0";
#endif

////////////////////////////////////////////////////////////////////////////////
//
// Global variables.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Local functions.
//
////////////////////////////////////////////////////////////////////////////////
/**
 * @name    LcdPalletColor
 * @brief   Get color pallet 24 bit RGB color
 * @ingroup Drivers
 *
 * Local function to get the pallet color for the passed index
 *
 * @param UINT8 PalletColorIndex
 *
 * @retval UINT32 24 bit RGB color
 *
 * Example Usage:
 * @code
 *    RGB = LcdPalletColor(1); 
 * @endcode
 */

UINT32 LcdPalletColor(UINT8 PalletColorIndex)
{
   //if(LcdPalletRam != NULL)
   //   return(*(LcdPalletRam + PalletColorIndex));
   //else
      return(DefaultPallet.pColorTable[PalletColorIndex].Reg);
}

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @name    DrvLcdDisplayGetVersion
 * @brief   Reports the LCD display driver verison
 * @ingroup Drivers
 *
 * This function returns LCD display driver version
 *
 * @param None 
 *
 * @retval const CHAR* -> version string
 *
 * Example Usage:
 * @code
 *    string = DrvLcdDisplayGetVersion();
 * @endcode
 */

const CHAR* DrvLcdDisplayGetVersion(void)
{
   return(DrvLcdDisplayVersion);
}

/**
 * @name    DrvLcdWritePixel
 * @brief   Writes the display memory pixel color data
 * @ingroup Drivers
 *
 * Function writes the display memory pixel color data
 *
 * @param UINT16 Row
 * @param UINT16 Column
 * @param UINT32 RGB color
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdWritePixel(1, 2, 0x0000FFEE); 
 * @endcode
 */

void DrvLcdWritePixel(UINT16 Row, UINT16 Column, UINT32 Color)
{
   UINT32   Address;
                                       //compute address
   Address = (((UINT32)Column) + (LCD_SCREEN_WIDTH * (UINT32)Row));
                                       //set pixel color
   *((UINT32*)LcdFrameAddress + Address) = Color;
}

/**
 * @name    DrvLcdReadPixel
 * @brief   Read the display memory pixel color data
 * @ingroup Drivers
 *
 * Function reads the display memory pixel color data
 *
 * @param UINT16 Row
 * @param UINT16 Column
 *
 * @retval RGB color
 *
 * Example Usage:
 * @code
 *    RGB = DrvLcdReadPixel(1, 2); 
 * @endcode
 */

UINT32 DrvLcdReadPixel(UINT16 Row, UINT16 Column)
{
   UINT32   Address;
   UINT32   Data;
                                       //compute address
   Address = (((UINT32)Column) + (LCD_SCREEN_WIDTH * (UINT32)Row));
                                       //read current pixel color
   Data = (*((UINT32*)LcdFrameAddress + Address));
   
   return(Data);
}

/**
 * @name    DrvLcdAutoIncrementAddress
 * @brief   Increments the cursor position in memory
 * @ingroup Drivers
 *
 * Function increments the cursor position in memory
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdAutoIncrementAddress(); 
 * @endcode
 */

void DrvLcdAutoIncrementAddress(void)
{
   if(LcdCurrentColumn < (LCD_SCREEN_WIDTH - 1))
   {
      LcdCurrentColumn++;              //move to next pixel
   }
   else if(LcdCurrentRow < (LCD_SCREEN_HEIGHT - 1))
   {
      LcdCurrentColumn = 0;            //wrap to beginning of next line
      LcdCurrentRow++;
   }
}

/**
 * @name    DrvLcdSetFrameAddress
 * @brief   Sets the ram frame start address for image
 * @ingroup Drivers
 *
 * Function sets the ram frame start address for image in memory
 *
 * @param void* Address
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdSetFrameAddress(RamArray); 
 * @endcode
 */

void DrvLcdSetFrameAddress(void* Address)
{
   LcdFrameAddress = Address;          //set frame address
}

/**
 * @name    DrvLcdGetFrameAddress
 * @brief   Gets the ram frame start address for image
 * @ingroup Drivers
 *
 * Function gets the ram frame start address for image in memory
 *
 * @param None 
 *
 * @retval void* 
 *
 * Example Usage:
 * @code
 *    Array = DrvLcdGetFrameAddress(); 
 * @endcode
 */

void* DrvLcdGetFrameAddress(void)
{
   return(LcdFrameAddress);            //get frame address
}

/**
 * @name    DrvLcdGetCurrentDisplayFrame
 * @brief   Gets the LCD controller frame start address
 * @ingroup Drivers
 *
 * Function gets the LCD controller frame start address for image being displayed currently
 *
 * @param None 
 *
 * @retval void* 
 *
 * Example Usage:
 * @code
 *    Array = DrvLcdGetCurrentDisplayFrame(); 
 * @endcode
 */

void* DrvLcdGetCurrentDisplayFrame(void)
{
   return((void*)LCDC_LSSAR);       //get current frame address
}

/**
 * @name    DrvLcdSetCurrentDisplayFrame
 * @brief   Sets the LCD controller frame start address
 * @ingroup Drivers
 *
 * Function sets the LCD controller frame start address for image to display
 *
 * @param void* Address
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    Array = DrvLcdSetCurrentDisplayFrame(); 
 * @endcode
 */

void DrvLcdSetCurrentDisplayFrame(void* Address)
{                                      //set the LCD display frame buffer pointer
   LCDC_LSSAR = (UINT32)Address;
}      

/**
 * @name    DrvLcdPalletInit
 * @brief   Initializes pallet colors
 * @ingroup Drivers
 *
 * Function sets LCD pallet colors (R,G,B)
 *
 * @param const _LcdPallet* Pallet
 * @param volatile UINT32* LcdPalletRam
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    Array = DrvLcdPalletInit(LcdPalletStruct, LcdPalletArray); 
 * @endcode
 */

void DrvLcdPalletInit( const _LcdPallet* pPallet, volatile UINT32* pLcdPalletRam )
{
   UINT16 index;
   
   for(index = 0; index < pPallet->NumberEntriesUsed; index++)
   {                                   //set the pallet colors
      *pLcdPalletRam++ = pPallet->pColorTable[index].Reg;
   }
   for( ; index < LCD_MAX_PALLET_ENTRIES; index++)
   {                                   //clear remaining pallet ram
      *pLcdPalletRam++ = 0x00000000;
   }
}

/**
 * @name    DrvLcdSetPenColor
 * @brief   Set pen color
 * @ingroup Drivers
 *
 * Function sets LCD pen color.  Used for line operations
 *
 * @param _LcdColor Color
 *
 * @retval _LcdColor oldColor 
 *
 * Example Usage:
 * @code
 *    oldColor = DrvLcdSetPenColor(NewColor); 
 * @endcode
 */

_LcdColor DrvLcdSetPenColor( _LcdColor Color )
{
   _LcdColor   oldColor;

   oldColor = LcdPenColor;
   LcdPenColor = Color;                //set current pen color

   return(oldColor);
}

/**
 * @name    DrvLcdGetPenColor
 * @brief   Get pen color
 * @ingroup Drivers
 *
 * Function gets LCD pen color
 *
 * @param None 
 *
 * @retval _LcdColor Color 
 *
 * Example Usage:
 * @code
 *    Color = DrvLcdGetPenColor(); 
 * @endcode
 */

_LcdColor DrvLcdGetPenColor( void )
{
   return(LcdPenColor);                //get current pen color
}

/**
 * @name    DrvLcdSetBrushColor
 * @brief   Sets brush color
 * @ingroup Drivers
 *
 * Function sets LCD brush color used for fill operations
 *
 * @param _LcdColor Color
 *
 * @retval _LcdColor Color 
 *
 * Example Usage:
 * @code
 *    oldColor = DrvLcdSetBrushColor(0x00FF00FF); 
 * @endcode
 */

_LcdColor DrvLcdSetBrushColor( _LcdColor Color )
{
   _LcdColor   oldColor;

   oldColor = LcdBrushColor;
   LcdBrushColor = Color;              //set current brush color

   return(oldColor);
}

/**
 * @name    DrvLcdGetBrushColor
 * @brief   Gets brush color
 * @ingroup Drivers
 *
 * Function gets LCD brush color used for fill operations
 *
 * @param None 
 *
 * @retval _LcdColor Color
 *
 * Example Usage:
 * @code
 *    Color = DrvLcdGetBrushColor(); 
 * @endcode
 */

_LcdColor DrvLcdGetBrushColor( void )
{
   return(LcdBrushColor);              //get current brush color
}

/**
 * @name    DrvLcdSetBackgroundColor
 * @brief   Set background color
 * @ingroup Drivers
 *
 * Function sets LCD color used when drawing the background
 *
 * @param _LcdColor Color 
 *
 * @retval _LcdColor Color
 *
 * Example Usage:
 * @code
 *    oldColor = DrvLcdSetBackgroundColor(Color); 
 * @endcode
 */

_LcdColor DrvLcdSetBackgroundColor( _LcdColor Color )
{
   _LcdColor   oldColor;

   oldColor = LcdBackgroundColor;
   LcdBackgroundColor = Color;         //set current background color

   return(oldColor);
}

/**
 * @name    DrvLcdGetBackgroundColor
 * @brief   Get background color
 * @ingroup Drivers
 *
 * Function gets LCD color used when drawing the background
 *
 * @param None 
 *
 * @retval _LcdColor Color
 *
 * Example Usage:
 * @code
 *    oldColor = DrvLcdSetBackgroundColor(); 
 * @endcode
 */

_LcdColor DrvLcdGetBackgroundColor( void )
{
   return(LcdBackgroundColor);         //get current background color
}

/**
 * @name    DrvLcdSetTextColor
 * @brief   Set text color
 * @ingroup Drivers
 *
 * Function sets LCD color used when drawing text
 *
 * @param _LcdColor Color 
 *
 * @retval _LcdColor Color
 *
 * Example Usage:
 * @code
 *    oldColor = DrvLcdSetTextColor(Color); 
 * @endcode
 */

_LcdColor DrvLcdSetTextColor( _LcdColor Color )
{
   _LcdColor   oldColor;

   oldColor = LcdTextColor;
   LcdTextColor = Color;               //set current text color

   return(oldColor);
}

/**
 * @name    DrvLcdGetTextColor
 * @brief   Get text color
 * @ingroup Drivers
 *
 * Function gets LCD color used when drawing text
 *
 * @param None 
 *
 * @retval _LcdColor Color
 *
 * Example Usage:
 * @code
 *    oldColor = DrvLcdGetTextColor(); 
 * @endcode
 */

_LcdColor DrvLcdGetTextColor( void )
{
   return(LcdTextColor);               //get current text color
}

/**
 * @name    DrvLcdSetAutoIncrementMode
 * @brief   Sets the current LCD increment mode
 * @ingroup Drivers
 *
 * Function sets the current LCD increment mode
 * * DRV_LCD_LOGICAL_OR_DATA
 * * DRV_LCD_LOGICAL_AND_DATA
 * * DRV_LCD_LOGICAL_XOR_DATA
 * * DRV_LCD_LOGICAL_WRITE_DATA
 *
 * @param UINT8 Mode
 *
 * @retval UINT8 oldMode
 *
 * Example Usage:
 * @code
 *    oldMode = DrvLcdSetAutoIncrementMode(DRV_LCD_LOGICAL_OR_DATA); 
 * @endcode
 */

UINT8 DrvLcdSetAutoIncrementMode(UINT8 Mode)
{
   UINT8 oldMode;

   oldMode = LcdWriteMode;
   LcdAddressAutoIncrement = Mode;     //set new autoincrement mode

   return(oldMode);                    //return old mode
}   

/**
 * @name    DrvLcdGetAutoIncrementMode
 * @brief   Gets the current LCD increment mode
 * @ingroup Drivers
 *
 * Function gets the current LCD increment mode
 * * DRV_LCD_LOGICAL_OR_DATA
 * * DRV_LCD_LOGICAL_AND_DATA
 * * DRV_LCD_LOGICAL_XOR_DATA
 * * DRV_LCD_LOGICAL_WRITE_DATA
 *
 * @param None 
 *
 * @retval UINT8 oldMode
 *
 * Example Usage:
 * @code
 *    oldMode = DrvLcdGetAutoIncrementMode(); 
 * @endcode
 */

UINT8 DrvLcdGetAutoIncrementMode( void )
{
   return(LcdAddressAutoIncrement);    //return current autoincrement mode
}   

/**
 * @name    DrvLcdInit
 * @brief   Initializes the LCD
 * @ingroup Drivers
 *
 * Function initializes the LCD controller and sets the default colors for pen, brush, text and background.
 *
 * @param UINT32 LCDPartNumber
 * @param UINT32 LCDController
 * @param void* FrameAddress
 * @param void* PalletAddress
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdInit(); 
 * @endcode
 */

void DrvLcdInit( UINT32 LCDPartNumber, UINT32 LcdController, void* FrameAddress, const _LcdPallet* PalletAddress )
{                                      //This matches the Solomon SysTech timing
   DrvLcdControllerInit(LCDPartNumber, 0);
                                       //set default frame address   
   DrvLcdSetPenColor( COLOR_YELLOW );
   DrvLcdSetBrushColor( COLOR_BLUE );
   DrvLcdSetTextColor( COLOR_WHITE );
   DrvLcdSetWriteMode(DRV_LCD_LOGICAL_WRITE_DATA);
   DrvLcdSetAutoIncrementMode(TRUE);
                                       //set background color to white
   DrvLcdSetBackgroundColor(COLOR_BLACK);
   DrvLcdSetFrameAddress(FrameAddress);
   DrvLcdCls();
   DrvBackLightOn();                   //Switch back light on.
}

/**
 * @name    DrvLcdSetCursorAt
 * @brief   Positions cursor
 * @ingroup Drivers
 *
 * Function moves the cursor to the desired row and column position
 *
 * @param UINT16 Row
 * @param UINT16 Column
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdSetCursorAt(10, 20); 
 * @endcode
 */

void DrvLcdSetCursorAt( UINT16 Row, UINT16 Column )
{
   if(Row > LCD_SCREEN_HEIGHT)         //set the x,y cursor position
      Row = LCD_SCREEN_HEIGHT;
   if(Column > LCD_SCREEN_WIDTH)
      Column = LCD_SCREEN_WIDTH;

   LcdCurrentRow = Row;
   LcdCurrentLine = Row / 8;
   LcdCurrentColumn = Column;
}

void DrvLcdSetDisplayOrigin(UINT16 x, UINT16 y)
{
	(void)x;
	LCDC_LSSAR = LCD_FRAME_ADDRESS + (y * LCD_SCREEN_WIDTH * 4) + x;
}

/**
 * @name    DrvLcdSetRowAt
 * @brief   Positions cursor
 * @ingroup Drivers
 *
 * Function moves the cursor to the desired row
 *
 * @param UINT16 Row
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdSetRowAt(10); 
 * @endcode
 */

void DrvLcdSetRowAt( UINT16 Row )
{
   if(Row > LCD_SCREEN_HEIGHT)         //set the y cursor position
      Row = LCD_SCREEN_HEIGHT;         //x position is not changed

   LcdCurrentRow = Row;
   LcdCurrentLine = Row / 8;
}

/**
 * @name    DrvLcdSetColumnAt
 * @brief   Positions cursor
 * @ingroup Drivers
 *
 * Function Moves the cursor to the desired column
 *
 * @param UINT16 Column
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdSetColumnAt(10); 
 * @endcode
 */

void DrvLcdSetColumnAt( UINT16 Column )
{                                      //set the x cursor position
   LcdCurrentColumn = Column;          //y position is not changed
}

void DrvLcdSetModifyRead( void )
{
}

void DrvLcdResetModifyRead( void )
{
}

volatile UINT8 DrvLcdReadStatus( UINT8 Mask )
{
   return(1);
}

volatile UINT8 DrvLcdDummyReadData( void )
{
   return(1);
}

/**
 * @name    DrvLcdReadData
 * @brief   Read LCD data
 * @ingroup Drivers
 *
 * Function reads the current Lcd pixel from display memory
 *
 * @param None 
 *
 * @retval volatile UINT32 RGB
 *
 * Example Usage:
 * @code
 *    RGB = DrvLcdReadData(); 
 * @endcode
 */

volatile UINT32 DrvLcdReadData( void )
{
   volatile UINT32 Data;
                                       //read current pixel data
   Data = DrvLcdReadPixel( LcdCurrentRow, LcdCurrentColumn );

   if(LcdAddressAutoIncrement)         //check if autoincrement address
   {
      DrvLcdAutoIncrementAddress();    //increment address
   }

   return(Data);                       //return pixel data
}

/**
 * @name    DrvLcdSetWriteMode
 * @brief   Set write mode
 * @ingroup Drivers
 *
 * Function sets LCD write mode, ORed, ANDed, XOR or WRITE mode and returns the old mode
 *
 * @param _DrvLcdDataMode Mode 
 *
 * @retval _DrvLcdDataMode oldMode
 *
 * Example Usage:
 * @code
 *    RGB = DrvLcdSetWriteMode(DRV_LCD_LOGICAL_WRITE_DATA); 
 * @endcode
 */

_DrvLcdDataMode DrvLcdSetWriteMode( _DrvLcdDataMode Mode )
{
   _DrvLcdDataMode oldMode;

   oldMode = LcdWriteMode;             
   LcdWriteMode = Mode;                //set the write mode

   return(oldMode);                    //return old write mode
}

/**
 * @name    DrvLcdReadWriteData
 * @brief   Read data and write with passed mask
 * @ingroup Drivers
 *
 * Function reads current LCD pixel data and writes the passed color to the current Lcd pixel using 
 * the passed mode mask
 * * DRV_LCD_LOGICAL_OR_DATA
 * * DRV_LCD_LOGICAL_AND_DATA
 * * DRV_LCD_LOGICAL_XOR_DATA
 * * DRV_LCD_LOGICAL_WRITE_DATA
 *
 * @param UINT32 Data
 * @param UINT8 Mode
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdReadWriteData(0x00FF8800, DRV_LCD_LOGICAL_WRITE_DATA); 
 * @endcode
 */

void DrvLcdReadWriteData(UINT32 Data, UINT8 Mask)
{
   volatile UINT32 CurrentLcdData;
                                       //read current pixel data
   CurrentLcdData = DrvLcdReadPixel( LcdCurrentRow, LcdCurrentColumn );

   switch(LcdWriteMode)
   {
      case DRV_LCD_LOGICAL_OR_DATA:    //logical or in new pixel color
         DrvLcdWritePixel( LcdCurrentRow, LcdCurrentColumn, CurrentLcdData | Data );
         break;

      case DRV_LCD_LOGICAL_AND_DATA:   //logical and in new pixel color
         DrvLcdWritePixel( LcdCurrentRow, LcdCurrentColumn, CurrentLcdData & Data );
         break;

      case DRV_LCD_LOGICAL_XOR_DATA:   //logical xor in new pixel color
         DrvLcdWritePixel( LcdCurrentRow, LcdCurrentColumn, CurrentLcdData ^ Data );
         break;

      case DRV_LCD_LOGICAL_WRITE_DATA: //write pixel color
         DrvLcdWritePixel( LcdCurrentRow, LcdCurrentColumn, Data );
         break;

      default:
         ;
   }

   if(LcdAddressAutoIncrement)         //check if autoincrement address
   {
      DrvLcdAutoIncrementAddress();    //increment address
   }
}

/**
 * @name    DrvLcdWriteData
 * @brief   Write data to LCD memory
 * @ingroup Drivers
 *
 * Function writes the passed color to the current Lcd pixel
 *
 * @param UINT32 Data
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdWriteData(0x00FF8800); 
 * @endcode
 */

void DrvLcdWriteData( UINT32 Color )
{                                      //write passed color to current x,y position
   DrvLcdWritePixel( LcdCurrentRow, LcdCurrentColumn, Color );

   if(LcdAddressAutoIncrement)         //check if autoincrement address
   {
      DrvLcdAutoIncrementAddress();    //increment address
   }
}

/**
 * @name    DrvSetContrast
 * @brief   Set LCD contrast
 * @ingroup Drivers
 *
 * Function sets the LCD contrast level
 *
 * @param UINT8 Contrast
 * @param UINT32 LCDPartNumber
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvSetContrast(0x12, LCD_MID_184_310); 
 * @endcode
 */

void DrvSetContrast( UINT8 Contrast, UINT32 LCDPartNumber )
{
   LcdContrast = Contrast;
}

/**
 * @name    DrvLcdWriteFrame
 * @brief   Writes the passed color to current Lcd frame
 * @ingroup Drivers
 *
 * Function writes the passed color to current Lcd frame.  Frame may or may not be LCD display frame
 *
 * @param UINT16 Row
 * @param UINT16 Column
 * @param UINT32 RGBColor
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdWriteFrame(1, 10, 0x00112233); 
 * @endcode
 */

void DrvLcdWriteFrame( UINT16 Row, UINT16 Column, UINT32 Color )
{
   DrvLcdWritePixel(Row, Column, Color);
}

/**
 * @name    DrvLcdCls
 * @brief   Clear current Lcd display memory
 * @ingroup Drivers
 *
 * Function clear current Lcd display memory and sets the cursor to 0, 0 position
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdCls(); 
 * @endcode
 */

void DrvLcdCls( void )
{
   UINT16 row;
   UINT16 column;

   for(row = 0; row < LCD_SCREEN_HEIGHT; row++)
   {
      for(column = 0; column < LCD_SCREEN_WIDTH; column++)
      {
         DrvLcdWritePixel(row, column, LcdBackgroundColor);
      }
   }   

   LcdCurrentRow = 0;                  //reset x,y position
   LcdCurrentLine = 0;
   LcdCurrentColumn = 0;
}

/**
 * @name    DrvLcdFill
 * @brief   
 * @ingroup Drivers
 *
 * Function 
 *
 * @param BOOL On
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdFill(); 
 * @endcode
 */

void DrvLcdFill( BOOL On )
{
   if( On )
   {
      //LcdWrite( LCD_RS_COMMAND, LCD_CMD_ENTIRE_DISPLAY_ON );
   }
   else
   {
      //LcdWrite( LCD_RS_COMMAND, LCD_CMD_ENTIRE_DISPLAY_NORMAL );
   }
}


/**
 * @name    DrvLcdDisplayGraphic
 * @brief   Displays graphic
 * @ingroup Drivers
 *
 * Function displays graphic passed at current row and column
 *
 * @param const void* Data
 * @param UINT16 GraphicWidth
 * @param UINT16 GraphicHeight
 * @param UINT16 ColorMode
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvDrvLcdDisplayGraphiccdFill(Array, 40, 40, LCD_COLOR_MODE_16BIT); 
 * @endcode
 */

void DrvLcdDisplayGraphic( const void* Data, UINT16 Width, UINT16 Height, UINT16 ColorMode )
{
   UINT16            CurrentRow;
   UINT16            CurrentColumn;
   UINT16            Row;
   UINT16            Column;
   _DrvLcdDataMode   oldMode;
   UINT8             oldIncrementMode;
   UINT8*            pColor8;
   UINT16*           pColor16;
   UINT32*           pColor32;
   UINT32            Color;

   pColor8 = (UINT8*)Data;
   pColor16 = (UINT16*)Data;
   pColor32 = (UINT32*)Data;
                                       //set to autoincrement the address
   oldIncrementMode = DrvLcdSetAutoIncrementMode(FALSE);   
                                       //set to write mode
   oldMode = DrvLcdSetWriteMode(DRV_LCD_LOGICAL_WRITE_DATA);
   
   CurrentRow = LcdCurrentRow;         //save current x,y position
   CurrentColumn = LcdCurrentColumn;

   for(Row = CurrentRow; Row < (CurrentRow + Height) && Row < LCD_SCREEN_HEIGHT; Row++)
   {
      for(Column = CurrentColumn; Column < (CurrentColumn + Width) && Column < LCD_SCREEN_WIDTH; Column++) 
      {
         if(ColorMode == LCD_COLOR_MODE_16BIT)
         {                             //compressed in 16 bit array, convert to 24 bit
            Color = (((UINT32)(*pColor16) & 0x0000001F) << (3 + 0)) | 
                    (((UINT32)(*pColor16) & 0x000007E0) << (2 + 3)) |
                    (((UINT32)(*pColor16) & 0x0000F800) << (3 + 5));
            pColor16++;
         }
         else if(ColorMode == LCD_COLOR_MODE_PALLET)
         {                             //lookup color from pallet
            Color = LcdPalletColor(*pColor8++);
         }
         else
         {                             //not compressed
            Color = *pColor32++;       //true 24 bit array
         }
         DrvLcdWritePixel(Row, Column, Color);
         //DrvLcdWriteFrame( Row, Column, Color );
      }
   }
                                       //move cursor
   DrvLcdSetCursorAt( CurrentRow, CurrentColumn + Width );
                                       //restore mode
   DrvLcdSetAutoIncrementMode(oldIncrementMode);
   DrvLcdSetWriteMode(oldMode);
}

/**
 * @name    DrvLcdLineFeed
 * @brief   Moves cursor new line
 * @ingroup Drivers
 *
 * Function moves the cursor position to beginning of new line for the font height passed
 *
 * @param UINT8 FontHeight
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdLineFeed(16); 
 * @endcode
 */

void DrvLcdLineFeed( UINT8 FontHeight )
{
   DrvLcdSetCursorAt( LcdCurrentRow + FontHeight, 0 );
}

/**
 * @name    DrvLcdBackLight
 * @brief   Backlight control
 * @ingroup Drivers
 *
 * Function sets the backlight state
 * * 0 -> OFF
 * * 1 -> ON
 *
 * @param UINT8 State
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdBackLight(0); 
 * @endcode
 */

void DrvLcdBackLight( UINT8 Mode )
{
   DrvBackLightState(Mode);            //back light on/off
}

/**
 * @name    DrvLcdBackLight
 * @brief   Backlight brightness control
 * @ingroup Drivers
 *
 * Function sets the backlight brightness level
 * * 0 -> OFF
 * * 1 -> ON
 *
 * @param _LcdBackLightLevel Level
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvBacklightLevelSelect(0); 
 * @endcode
 */

void DrvBacklightLevelSelect(_LcdBackLightLevel Level)
{
}

