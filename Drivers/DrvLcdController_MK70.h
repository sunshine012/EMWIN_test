
/**
 * @file   DrvLcdController_MK70.h
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Definitions for MK70 LCD controller
 *
 * Contains the definitions for MK70 LCD controller
 */
 
/******************************************************************************
* Includes
******************************************************************************/
#include "DrvTypeDefs.h"
#include "Cpu.h"
#include "DrvIOPort.h"

/******************************************************************************
* Constants
******************************************************************************/

#ifndef _DRV_LCD_CONTROLLER_MK70_H_
#define _DRV_LCD_CONTROLLER_MK70_H_

#define LCD_PE_MODE
#define USE_EMWIN	

#define LCD_CLK               6000000  //!< LCD clock 6.000MHz
                                       //! System clock / (LCDHWFB_PANEL_CLKDIV + 1) = LCD_CLK
#define LCDHWFB_PANEL_CLKDIV  ((CPU_CORE_CLK_HZ / LCD_CLK) - 1)       

                                       //! LCD D0-D12 I/O special function register
#define LCD_D0_D12_SFR        PORTE_BASE_PTR
                                       //! LCD D13-D23 I/O special functionregister
#define LCD_D13_D23_SFR       PORTF_BASE_PTR
                                       //! LCD Control line I/O special function register
#define LCD_CONTROL_SFR       PORTD_BASE_PTR
                                       //! LCD D0-D12 I/O port register
#define LCD_D0_D12_PORT       PTE_BASE_PTR    
                                       //! LCD D13-D23 I/O port register
#define LCD_D13_D23_PORT      PTF_BASE_PTR    
                                       //! LCD Control line I/O port register
#define LCD_CONTROL_PORT      PTD_BASE_PTR  
  
#define LCD_D0_BIT            0        //!< LCD D0 port pin bit
#define LCD_D1_BIT            1        //!< LCD D1 port pin bit
#define LCD_D2_BIT            2        //!< LCD D2 port pin bit
#define LCD_D3_BIT            3        //!< LCD D3 port pin bit
#define LCD_D4_BIT            4        //!< LCD D4 port pin bit
#define LCD_D5_BIT            5        //!< LCD D5 port pin bit
#define LCD_D6_BIT            6        //!< LCD D6 port pin bit
#define LCD_D7_BIT            7        //!< LCD D7 port pin bit
#define LCD_D8_BIT            8        //!< LCD D8 port pin bit
#define LCD_D9_BIT            9        //!< LCD D9 port pin bit
#define LCD_D10_BIT           10       //!< LCD D10 port pin bit
#define LCD_D11_BIT           11       //!< LCD D11 port pin bit
#define LCD_D12_BIT           12       //!< LCD D12 port pin bit
#define LCD_D13_BIT           17       //!< LCD D13 port pin bit
#define LCD_D14_BIT           18       //!< LCD D14 port pin bit
#define LCD_D15_BIT           19       //!< LCD D15 port pin bit
#define LCD_D16_BIT           20       //!< LCD D16 port pin bit
#define LCD_D17_BIT           21       //!< LCD D17 port pin bit
#define LCD_D18_BIT           22       //!< LCD D18 port pin bit
#define LCD_D19_BIT           23       //!< LCD D19 port pin bit          
#define LCD_D20_BIT           24       //!< LCD D20 port pin bit
#define LCD_D21_BIT           25       //!< LCD D21 port pin bit
#define LCD_D22_BIT           26       //!< LCD D22 port pin bit
#define LCD_D23_BIT           27       //!< LCD D23 port pin bit
#define LCD_CLOCK_BIT         12       //!< LCD Clock port pin bit
#define LCD_DE_BIT            13       //!< LCD Data Enable port pin bit
#define LCD_HSYNC_BIT         14       //!< LCD Horizontal sync port pin bit
#define LCD_VSYNC_BIT         15       //!< LCD Vertical sync port pin bit
#define LCD_CONTRAST_BIT      11       //!< LCD contrast port pin bit

                                       //! LCD CS I/O special function register
#define LCD_CS_IO_SFR         PORTD_BASE_PTR
                                       //! LCD CS I/O port register
#define LCD_CS_IO_PORT        PTD_BASE_PTR
#define LCD_CS_IO_BIT         10       //!< LCD CS port pin bit

                                       //! LCD Backlight I/O special function register
#define LCD_BKL_IO_SFR        PORTF_BASE_PTR
                                       //! LCD Backlight I/O port register
#define LCD_BKL_IO_PORT       PTF_BASE_PTR
#define LCD_BLK_IO_BIT        16       //!< LCD Backlight port pin bit

                                       //! LCD Frame base address
#define LCD_FRAME_ADDRESS     0x80000000
                                       //! LCD Screen height in pixels
#define LCD_SCREEN_HEIGHT     (UINT32)240
                                       //! LCD Screen width in pixels
#define LCD_SCREEN_WIDTH      (UINT32)320
                                       //! LCD Screen column count
#define LCD_COLUMN_COUNT      LCD_SCREEN_WIDTH
                                       //! LCD Screen page count
#define LCD_PAGE_COUNT        LCD_SCREEN_HEIGHT
                                       //! Bits per pixel
#define LCD_BPP               (UINT32)24

#define LCD_COLOR_MODE_PALLET 0xE000   //!< compressed pallet
#define LCD_COLOR_MODE_16BIT  0x8000   //!< compressed 5:6:5 RGB mode
#define LCD_COLOR_MODE_24BIT  0xC000   //!< uncompressed 8:8:8 RGB mode

/******************************************************************************
* Types
******************************************************************************/

/******************************************************************************
* Macros 
******************************************************************************/
  
                                       //! LCD Chip select low macro
#define DrvLcdCsLow()            (LCD_CS_IO_PORT->PCOR = (0x00000001 << LCD_CS_IO_BIT))
                                       //! LCD Chip select high macro
#define DrvLcdCsHigh()           (LCD_CS_IO_PORT->PSOR = (0x00000001 << LCD_CS_IO_BIT))

                                       //! LCD Backlight on macro
#define DrvBackLightOn()         (LCD_BKL_IO_PORT->PSOR = (0x00000001 << LCD_BLK_IO_BIT))
                                       //! LCD Backlight off macro
#define DrvBackLightOff()        (LCD_BKL_IO_PORT->PCOR = (0x00000001 << LCD_BLK_IO_BIT))
                                       //! Get LCD Backlight state
#define DrvBackLightState(State) DrvIOSetPortBitData(LCD_BKL_IO_PORT, LCD_BLK_IO_BIT, State)
                                       //! LCD Backlight toggle macro
#define DrvBackLightToggle()     (LCD_BKL_IO_PORT->PTOR = (0x00000001 << LCD_BLK_IO_BIT))
                                       //! LCD Contrast low macro
#define DrvLcdContrastLow()      (LCD_CONTROL_PORT->PCOR = (0x00000001 << LCD_CONTRAST_BIT))
                                       //! LCD Contrast high macro
#define DrvLcdContrastHigh()     (LCD_CONTROL_PORT->PSOR = (0x00000001 << LCD_CONTRAST_BIT))
/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/
    
const CHAR* DrvLcdControllerGetVersion(void);
UINT8 DrvLcdControllerInit(UINT32 LcdControllerId, UINT32 LcdModuleId);
void DrvLcdPowerOff( void );


#endif
