
/**
 * @file   DrvLcdController_MK70.c
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Driver for MK70 LCD controller
 *
 * This file implements the driver functions for the MK70 LCD Controller
 */

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////



//#ifndef NO_D4D
//#include "d4d_user_cfg.h"
//#endif

#include "DrvLcdController_MK70.h"
#include "DrvSsp.h"
#include "DrvSpi.h"
#include "LCDC1.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

#if (DRV_LIB_REV == 1000)
const char DrvLcdControllerVersion[] = "1.0.0.0";
#else
const char DrvLcdControllerVersion[] = "2.0.0.0";
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
 * @name    LcdDelayMs
 * @brief   LCD delay
 * @ingroup Drivers
 *
 * Local function delay approximately 1ms delay with 120MHz core clock
 *
 * @param uint32 Delay -> in milliseconds 
 *
 * @retval None 
 *
 * Example Usage:
 * @code
 *    LcdDelayMs(10);  //10ms delay
 * @endcode
 */

void LcdDelayMs(uint32 Delay)
{
   volatile uint32 Count;

   for(; Delay > 0; Delay--)
   {
      for(Count = 8000; Count > 0; Count--)
      {                             //1.0ms with core clock of 120MHz
         asm("nop");                    
      }
      asm("nop");                    
      asm("nop");                    
      asm("nop");                    
      asm("nop");                    
   }
}

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @name    DrvLcdControllerGetVersion
 * @brief   Reports the LCD controller driver verison
 * @ingroup Drivers
 *
 * This function returns LCD controller driver version
 *
 * @param None 
 *
 * @retval const char* -> version string
 *
 * Example Usage:
 * @code
 *    string = DrvLcdControllerGetVersion();
 * @endcode
 */

const char* DrvLcdControllerGetVersion(void)
{
   return(DrvLcdControllerVersion);
}

/**
 * @name    LcdControllerInitCasilCtm320240N11
 * @brief   LCD controller initialization
 * @ingroup Drivers
 *
 * Function initializes the MK70 LCD controller parameters for the CTM320240N11 TFT
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    LcdControllerInitCasilCtm320240N11();
 * @endcode
 */

void LcdControllerInitCasilCtm320240N11(void)
{  
#ifdef NO_D4D                          //
   LCDC_LSSAR = LCD_FRAME_ADDRESS;

   LCDC_LSR = LCDC_LSR_XMAX(LCD_SCREEN_WIDTH / 16) | LCDC_LSR_YMAX(LCD_SCREEN_HEIGHT);
   LCDC_LVPWR = LCDC_LVPWR_VPW(LCD_SCREEN_WIDTH);

   LCDC_LCPR = 0;                      //Cursor off
   LCDC_LCWHB = 0;                     //
   LCDC_LCCMR = 0;
#endif
   LCDC_LPOR = 0;                      //set LCD panning offset
   LCDC_LGWPR = 0;                     //

                                       //set LCD panel configuration
   LCDC_LPCR = LCDC_LPCR_TFT_MASK |    //TFT Screen
               LCDC_LPCR_COLOR_MASK |  //Color
                                       
               LCDC_LPCR_BPIX(7) |     //bpp = 24bit  
                                       //pixel polarity
               LCDC_LPCR_FLMPOL_MASK | //first line marker active low      
               LCDC_LPCR_LPPOL_MASK |  //line pulse active low     
                                       //Use big-endian mode (0xFFAA5500 means R=AA,G=55,B=00)
               LCDC_LPCR_END_SEL_MASK |           
                                       //Enable LSCLK when vsync is idle
               LCDC_LPCR_SCLKIDLE_MASK |       
                                       //Always enable clock
               LCDC_LPCR_SCLKSEL_MASK |      
               LCDC_LPCR_CLKPOL_MASK | //Active on positive edge of LSCLK. In TFT mode, active on negative edge of LSCLK.     
                                       //Divide 120 PLL clock by (23+1)=24 to get 5.000MHz clock
               LCDC_LPCR_PCD(LCDHWFB_PANEL_CLKDIV);             
  
                                       //set LCD horizontal configuration based on panel data
   LCDC_LHCR = LCDC_LHCR_H_WIDTH(1) |  //(1+1)=2 SCLK period for HSYNC activated
               LCDC_LHCR_H_WAIT_1(19) |//(19+1)=20 SCLK period between end of OE and beginning of HSYNC
               LCDC_LHCR_H_WAIT_2(63); //(63+3)=66 SCLK periods between end of HSYNC and beginning of OE

                                       //Set LCD vertical configuration based on panel data
   LCDC_LVCR = LCDC_LVCR_V_WIDTH(1) |  //1 SCLK period for VSYNC activated
               LCDC_LVCR_V_WAIT_1(4) | //4 SCLK period between end of OE and beginning of VSYNC
               LCDC_LVCR_V_WAIT_2(18); //18 SCLK periods between end of VSYNC and beginning of OE
   
#ifndef NO_D4D
#if( D4DLCDHWFB_DOUBLE_BUFFER == 1 )
   DrvEnableInt(INT_LCD, 3);
#endif
#if( D4DLCDHWFB_DMA_ENABLE == 1 )
   DrvEnableInt(INT_DMA0_DMA16, 3);
#endif
#endif

#ifdef NO_D4D                          //
   LCDC_LPCCR = 0;                     //PWM contrast off
   LCDC_LDCR = 0x00040060;             //
   SIM_MCR |= SIM_MCR_LCDSTART_MASK;   //start LCD controller 
#endif
}

/**
 * @name    Hx823dWriteCmd
 * @brief   HX8238D write command
 * @ingroup Drivers
 *
 * Function writes command to the HX8238D controller via the SPI port for the TFT.  SPI must be initialize first
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    Hx823dWriteCmd();
 * @endcode
 */

void Hx823dWriteCmd(UINT16 Register, UINT16 Data)
{
   DrvSspSpiWrite(2, 0x71);
   DrvSspSpiWrite16(2, Register);
   DrvSspSpiWrite16(2, Data);
}

/**
 * @name    Hx8238dInit
 * @brief   HX8238D controller initialization
 * @ingroup Drivers
 *
 * Function initializes the HX8238D controller for the TFT.  SPI must be initialize first
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    Hx8238dInit();
 * @endcode
 */

void Hx8238dInit(void)
{
   DrvSpiSelectDevice(SPI_DEVICE_LCD);
   Hx823dWriteCmd(0x0001, 0x6300);     //CPE=1, charge pump on, REV = 1, not reversed, PINV = 0,
                                       //RGB mode, SM = 0, TB = 1, data shift 0 to 239 
   Hx823dWriteCmd(0x0002, 0x0200);     //B/C = 1 line inv, 
   Hx823dWriteCmd(0x0003, 0x7166);     //Power1, VGH, VGL
   Hx823dWriteCmd(0x0004, 0x0447);     //SEL2-0 = 000, PALM = 1 (288 lines), BLT = 00 (10 fields)
   Hx823dWriteCmd(0x0005, 0xBCD4);     //DEP=1, CKP = 1, VSP = 0, HSP = 0
   Hx823dWriteCmd(0x000A, 0x3F08);     //Brightness = 0x3F / contrast = 0x08
   Hx823dWriteCmd(0x000B, 0xD400);     //Frame cycle
   Hx823dWriteCmd(0x000D, 0x123A);     //Power2, VDS = 2.2V, VRC Charge Pump 5.3V, Vref*4.312 = 3.07, VLCD63=5.39V
   Hx823dWriteCmd(0x000E, 0x2A00);     //Power3, VLCD63 * 1.2450 -> VCOML= 6.71V
   Hx823dWriteCmd(0x000F, 0x0000);     //Gate Scan
   Hx823dWriteCmd(0x0016, 0x9F80);     //Number of lines 319
   Hx823dWriteCmd(0x0017, 0x1406);     //Horizontal back porch = 0x14, Vertical back porch = 0x06
   Hx823dWriteCmd(0x001E, 0x00D4);     //power4, VCOMH=3.6V, SPI 
   DrvSpiSelectDevice(SPI_DEVICE_NONE);
}

/**
 * @name    LcdInitPins
 * @brief   LCD I/O pin initialization
 * @ingroup Drivers
 *
 * Local function initializes the LCD controller pins for LCD operation for 24 bit color operation
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    Hx8238dInit();
 * @endcode
 */

void LcdInitPins(void)
{
   DrvBackLightOff();                  //configure backlight I/O
   DrvIOSetPortPinDirection(LCD_BKL_IO_PORT, LCD_BLK_IO_BIT, IO_PORT_DDR_OUTPUT);
   DrvIOSetPortParFunction(LCD_BKL_IO_SFR, LCD_BLK_IO_BIT, IO_PORT_PIN_IO_GPIO);
   DrvLcdCsHigh();                     //configure LCD SPI chip select line
   DrvIOSetPortPinDirection(LCD_CS_IO_PORT, LCD_CS_IO_BIT, IO_PORT_DDR_OUTPUT);
   DrvIOSetPortParFunction(LCD_CS_IO_SFR, LCD_CS_IO_BIT, IO_PORT_PIN_IO_GPIO);
   DrvLcdContrastHigh();               //contrast
   DrvIOSetPortPinDirection(LCD_CONTROL_PORT, LCD_CONTRAST_BIT, IO_PORT_DDR_OUTPUT);
   DrvIOSetPortParFunction(LCD_CONTROL_SFR, LCD_CONTRAST_BIT, IO_PORT_PIN_IO_GPIO);

#ifndef LCD_PE_MODE   
                                       //configure the I/O pins for LCD operation
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D0_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D1_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D2_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D3_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D4_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D5_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D6_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D7_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D8_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D9_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D10_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D11_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D0_D12_SFR, LCD_D12_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D13_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D14_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D15_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D16_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D17_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D18_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D19_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D20_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D21_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D22_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_D13_D23_SFR, LCD_D23_BIT, IO_PORT_PIN_IO_FUNCTION7);
                                       //configure LCD control lines
   DrvIOSetPortParFunction(LCD_CONTROL_SFR, LCD_CLOCK_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_CONTROL_SFR, LCD_DE_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_CONTROL_SFR, LCD_HSYNC_BIT, IO_PORT_PIN_IO_FUNCTION7);
   DrvIOSetPortParFunction(LCD_CONTROL_SFR, LCD_VSYNC_BIT, IO_PORT_PIN_IO_FUNCTION7);
#endif
}  
   
/**
 * @name    DrvLcdControllerInit
 * @brief   LCD I/O pin initialization
 * @ingroup Drivers
 *
 * Function initialization of this LCD panel controller.  
 * * Selects the LCD clock source
 * * Initializes the LCD pins
 * * Initializes the LCD controller
 *
 * @param uint32 LcdControllerId 
 * @param uint32 LcdModule
 *
 * @retval UINT8 TRUE  -> Success  
 * @retval UINT8 FALSE -> Failed
 *
 * Example Usage:
 * @code
 *    Status = DrvLcdControllerInit(ControlerPartNumber, LCDPartNumber);
 * @endcode
 */

UINT8 DrvLcdControllerInit(uint32 LcdControllerId, uint32 LcdModuleId)
{
   UINT8 result = TRUE;

#ifndef LCD_PE_MODE
   SIM_SOPT2 &= ~SIM_SOPT2_LCDCSRC(3); //clear LCDC clock source
   SIM_SOPT2 |= SIM_SOPT2_LCDCSRC(2);  //select LCDC clock source PLL1
   SIM_SCGC3 |= SIM_SCGC3_LCDC_MASK;   //Enable LCDC
   LcdInitPins();					   //configure LCD pins
   switch(LcdControllerId)
   {
	  default:
		 Hx8238dInit(); 			   //SPI initialization of LCD module controller
   }

   switch(LcdModuleId)
   {								   //Initialization for MK70 LCD controller for
	  default:						   //CTM32024N11 LCD
		 LcdControllerInitCasilCtm320240N11();
   }
   DrvBackLightOn();				   //backlight on
   
#else
	DrvSpiSelectDevice(SPI_DEVICE_NONE);
	switch(LcdControllerId)
	{
	 default:
		Hx8238dInit();				  //SPI initialization of LCD module controller
	}

	LcdInitPins();
	switch(LcdModuleId)
	{								   //Initialization for MK70 LCD controller for
		default:						   //CTM32024N11 LCD
			(void)LCDC1_Init(NULL);
	}
	DrvBackLightOn();
#endif
	
   return(result);
}


/**
 * @name    DrvLcdPowerOff
 * @brief   LCD power down
 * @ingroup Drivers
 *
 * Function performs the LCD power down sequence
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvLcdPowerOff();
 * @endcode
 */

void DrvLcdPowerOff( void )
{
   
   DrvBackLightOff();                  //Switch back light off.
                                       //Turn display off.
                                       //Switch off power circuits (see spec).
   LcdDelayMs( 100 );
   LcdDelayMs( 10 );
   LcdDelayMs( 10 );
}

