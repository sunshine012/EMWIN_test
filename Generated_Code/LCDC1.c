/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : LCDC1.c
**     Project     : PE_Test
**     Processor   : MK70FN1M0VMJ15
**     Component   : LCDC_LDD
**     Version     : Component 01.025, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-08-21, 10:46, # CodeGen: 126
**     Abstract    :
**
**     Settings    :
**          Component name                                 : LCDC1
**          Device                                         : LCDC
**          Interrupt service                              : Disabled
**          Panel type                                     : TFT
**            Bits per pixel                               : 24
**            Width in pixels                              : 320
**            Height in pixels                             : 240
**            Endian select                                : Big
**            Signal polarity                              : 
**              Pixel polarity                             : Active high
**              HSYNC polarity                             : Active low
**              VSYNC polarity                             : Active low
**              Output enable (OE) polarity                : Active high
**              Pixel clock polarity                       : Active high
**            Display timing                               : 
**              Pixel clock                                : 6 MHz
**              Pixel clock period                         :  166.667 ns
**              PixClk and OE during sync                  : Always on
**              Horizontal                                 : 
**                HSYNC pulse width                        : 2
**                HSYNC pulse width                        :  333.334 ns
**                Front porch width                        : 20
**                Front porch width                        :  3333.34 ns
**                Back porch width                         : 66
**                Back porch width                         :  11000.022 ns
**                Total line width                         : 408
**                Total line width                         :  68.00408 us
**              Vertical                                   : 
**                VSYNC pulse width                        : 1
**                VSYNC pulse width                        :  68.00408 us
**                Front porch width                        : 4
**                Front porch width                        :  272.01632 us
**                Back porch width                         : 18
**                Back porch width                         :  1224.07344 us
**              Contrast control                           : Disabled
**          Settings                                       : TFT
**            HW cursor initialization                     : Enabled
**              Arithmetic operation                       : Cursor disabled
**              X-position                                 : 0
**              Y-position                                 : 0
**              Cursor width                               : 0
**              Cursor height                              : 0
**              Blinking                                   : Disabled
**              Blinking rate                              : 1
**              Cursor blink frequency                     : 32 Hz (31 ms)
**              Cursor color                               : 
**                Red                                      : 0
**                Green                                    : 0
**                Blue                                     : 0
**            Plane 0 initialization                       : Enabled
**              External object declaration                : 
**              Address                                    : 0x80000000
**              Vertical scan direction                    : Normal
**              Width in pixels                            : 320
**              Height in pixels                           : 240
**              Window position X                          : 0
**              Window position Y                          : 0
**              Window width                               : 320
**              Window height                              : 240
**              Position on screen X                       : 0
**              Position on screen Y                       : 0
**            Plane 1 initialization                       : Disabled
**          Pins                                           : TFT, 24 bit bus
**            LCD Data Red[0]                              : Enabled
**              Red[0] pin                                 : PTF20/SPI2_PCS1/FTM2_CH0/UART5_TX/GLCD_D16
**              Red[0] pin signal                          : 
**            LCD Data Red[1]                              : Enabled
**              Red[1] pin                                 : ADC3_SE6b/PTF21/FTM2_CH1/UART5_RTS_b/GLCD_D17
**              Red[1] pin signal                          : 
**            LCD Data Red[2]                              : Enabled
**              Red[2] pin                                 : ADC3_SE7b/PTF22/I2C0_SCL/FTM1_CH0/UART5_CTS_b/GLCD_D18
**              Red[2] pin signal                          : 
**            LCD Data Red[3]                              : Enabled
**              Red[3] pin                                 : ADC3_SE10/PTF23/I2C0_SDA/FTM1_CH1/TRACE_CLKOUT/GLCD_D19
**              Red[3] pin signal                          : 
**            LCD Data Red[4]                              : Enabled
**              Red[4] pin                                 : ADC3_SE11/PTF24/CAN1_RX/FTM1_QD_PHA/TRACE_D3/GLCD_D20
**              Red[4] pin signal                          : 
**            LCD Data Red[5]                              : Enabled
**              Red[5] pin                                 : ADC3_SE12/PTF25/CAN1_TX/FTM1_QD_PHB/TRACE_D2/GLCD_D21
**              Red[5] pin signal                          : 
**            LCD Data Red[6]                              : Enabled
**              Red[6] pin                                 : ADC3_SE13/PTF26/FTM2_QD_PHA/TRACE_D1/GLCD_D22
**              Red[6] pin signal                          : 
**            LCD Data Red[7]                              : Enabled
**              Red[7] pin                                 : ADC3_SE14/PTF27/FTM2_QD_PHB/TRACE_D0/GLCD_D23
**              Red[7] pin signal                          : 
**            LCD Data Green[0]                            : Enabled
**              Green[0] pin                               : ADC2_SE16/PTE8/I2S0_RXD1/UART5_TX/I2S0_RX_FS/GLCD_D8/FTM3_CH3
**              Green[0] pin signal                        : 
**            LCD Data Green[1]                            : Enabled
**              Green[1] pin                               : ADC2_SE17/PTE9/I2S0_TXD1/UART5_RX/I2S0_RX_BCLK/GLCD_D9/FTM3_CH4
**              Green[1] pin signal                        : 
**            LCD Data Green[2]                            : Enabled
**              Green[2] pin                               : PTE10/UART5_CTS_b/I2S0_TXD0/GLCD_D10/FTM3_CH5
**              Green[2] pin signal                        : 
**            LCD Data Green[3]                            : Enabled
**              Green[3] pin                               : ADC3_SE16/PTE11/UART5_RTS_b/I2S0_TX_FS/GLCD_D11/FTM3_CH6
**              Green[3] pin signal                        : 
**            LCD Data Green[4]                            : Enabled
**              Green[4] pin                               : ADC3_SE17/PTE12/I2S0_TX_BCLK/GLCD_D12/FTM3_CH7
**              Green[4] pin signal                        : 
**            LCD Data Green[5]                            : Enabled
**              Green[5] pin                               : PTF17/SPI2_SCK/FTM0_CH4/UART0_RX/GLCD_D13
**              Green[5] pin signal                        : 
**            LCD Data Green[6]                            : Enabled
**              Green[6] pin                               : PTF18/SPI2_SOUT/FTM1_CH0/UART0_TX/GLCD_D14
**              Green[6] pin signal                        : 
**            LCD Data Green[7]                            : Enabled
**              Green[7] pin                               : PTF19/SPI2_SIN/FTM1_CH1/UART5_RX/GLCD_D15
**              Green[7] pin signal                        : 
**            LCD Data Blue[0]                             : Enabled
**              Blue[0] pin                                : ADC1_SE4a/PTE0/SPI1_PCS1/UART1_TX/SDHC0_D1/GLCD_D0/I2C1_SDA/RTC_CLKOUT
**              Blue[0] pin signal                         : 
**            LCD Data Blue[1]                             : Enabled
**              Blue[1] pin                                : ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/GLCD_D1/I2C1_SCL/SPI1_SIN
**              Blue[1] pin signal                         : 
**            LCD Data Blue[2]                             : Enabled
**              Blue[2] pin                                : ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/GLCD_D2
**              Blue[2] pin signal                         : 
**            LCD Data Blue[3]                             : Enabled
**              Blue[3] pin                                : ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/GLCD_D3/SPI1_SOUT
**              Blue[3] pin signal                         : 
**            LCD Data Blue[4]                             : Enabled
**              Blue[4] pin                                : PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/SDHC0_D3/GLCD_D4
**              Blue[4] pin signal                         : 
**            LCD Data Blue[5]                             : Enabled
**              Blue[5] pin                                : PTE5/SPI1_PCS2/UART3_RX/SDHC0_D2/GLCD_D5/FTM3_CH0
**              Blue[5] pin signal                         : 
**            LCD Data Blue[6]                             : Enabled
**              Blue[6] pin                                : PTE6/SPI1_PCS3/UART3_CTS_b/I2S0_MCLK/GLCD_D6/FTM3_CH1/USB_SOF_OUT
**              Blue[6] pin signal                         : 
**            LCD Data Blue[7]                             : Enabled
**              Blue[7] pin                                : PTE7/UART3_RTS_b/I2S0_RXD0/GLCD_D7/FTM3_CH2
**              Blue[7] pin signal                         : 
**            Pixel clock pin                              : Enabled
**              Pixel clock pin                            : PTD12/SPI2_SCK/FTM3_FLT0/SDHC0_D4/FBa_A20/GLCD_PCLK
**              Pixel clock pin signal                     : 
**            VSYNC                                        : Enabled
**              VSYNC pin                                  : PTD15/SPI2_PCS1/SDHC0_D7/FBa_A23/GLCD_VFS
**              VSYNC pin signal                           : 
**            HSYNC                                        : Enabled
**              HSYNC pin                                  : PTD14/SPI2_SIN/SDHC0_D6/FBa_A22/GLCD_HFS
**              HSYNC pin signal                           : 
**            Output enable pin                            : Enabled
**              OE pin                                     : PTD13/SPI2_SOUT/SDHC0_D5/FBa_A21/GLCD_DE
**              OE pin signal                              : 
**            Contrast pin                                 : Enabled
**              Contrast pin                               : PTD11/SPI2_PCS0/UART5_CTS_b/SDHC0_CLKIN/FBa_A19/GLCD_CONTRAST
**              Constrast pin signal                       : 
**          DMA                                            : 
**            Layer 0                                      : 
**              Burst length                               : Dynamic
**              High mark                                  : 4
**              Trigger mark                               : 96
**            Layer 1                                      : 
**              Burst length                               : Dynamic
**              High mark                                  : 4
**              Trigger mark                               : 96
**          Initialization                                 : 
**            Enable module                                : yes
**            Start in self-refresh mode                   : no
**            Event mask                                   : 
**              OnError                                    : Disabled
**              OnEndOfFrame                               : Disabled
**              OnStartOfFrame                             : Disabled
**            Auto initialization                          : no
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init                   - LDD_TDeviceData* LCDC1_Init(LDD_TUserData *UserDataPtr);
**         SetupBitmap            - LDD_TError LCDC1_SetupBitmap(LDD_TDeviceData *DeviceDataPtr,...
**         SetupWindow            - LDD_TError LCDC1_SetupWindow(LDD_TDeviceData *DeviceDataPtr,...
**         SetupWindowPosOnScreen - LDD_TError LCDC1_SetupWindowPosOnScreen(LDD_TDeviceData *DeviceDataPtr,...
**         Main                   - void LCDC1_Main(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file LCDC1.c
** @version 01.02
** @brief
**
*/         
/*!
**  @addtogroup LCDC1_module LCDC1 module documentation
**  @{
*/         

/* MODULE LCDC1. */
/* {Default RTOS Adapter} No RTOS includes */
#include "LCDC1.h"

#ifdef __cplusplus
extern "C" {
#endif 
/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static LCDC1_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
 

#define INIT_L0_BITMAP 0x01U
#define INIT_L0_WINDOW 0x02U
#define INIT_L0_DONE 0x03U
#define INIT_L1_BITMAP 0x04U
#define INIT_L1_WINDOW 0x08U
#define INIT_L1_DONE 0x0CU

#define LCDC1_INIT_EVENTS_MASK 0U
/*
** ===================================================================
**     Method      :  LCDC1_Init (component LCDC_LDD)
*/
/*!
**     @brief
**         Initializes the device and allocates memory for the private
**         device data structure.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* LCDC1_Init(LDD_TUserData *UserDataPtr)
{
  LCDC1_TDeviceData *DeviceDataPrv;
  LDD_LCDC_TBitmap BitmapInfo;
  LDD_LCDC_TWindow WindowInfo;
  /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;

  LCDC_PDD_DisableLCD(LCDC_BASE_PTR); /* Disable LCD */

  /* Pin initialization */
  /* PORTD_PCR12: ISF=0,MUX=7 */
  PORTD_PCR12 = (uint32_t)((PORTD_PCR12 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  PORT_PDD_SetPinDriveStrength(PORTD_BASE_PTR, 0x0CU, PORT_PDD_DRIVE_STRENGTH_HIGH);
  /* Red */
  /* PORTF_PCR20: ISF=0,MUX=5 */
  PORTF_PCR20 = (uint32_t)((PORTF_PCR20 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));
  /* PORTF_PCR21: ISF=0,MUX=7 */
  PORTF_PCR21 = (uint32_t)((PORTF_PCR21 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTF_PCR22: ISF=0,MUX=7 */
  PORTF_PCR22 = (uint32_t)((PORTF_PCR22 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTF_PCR23: ISF=0,MUX=7 */
  PORTF_PCR23 = (uint32_t)((PORTF_PCR23 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTF_PCR24: ISF=0,MUX=7 */
  PORTF_PCR24 = (uint32_t)((PORTF_PCR24 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTF_PCR25: ISF=0,MUX=7 */
  PORTF_PCR25 = (uint32_t)((PORTF_PCR25 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTF_PCR26: ISF=0,MUX=7 */
  PORTF_PCR26 = (uint32_t)((PORTF_PCR26 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTF_PCR27: ISF=0,MUX=7 */
  PORTF_PCR27 = (uint32_t)((PORTF_PCR27 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));

  /* Green */
  /* PORTE_PCR8: ISF=0,MUX=5 */
  PORTE_PCR8 = (uint32_t)((PORTE_PCR8 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR9: ISF=0,MUX=5 */
  PORTE_PCR9 = (uint32_t)((PORTE_PCR9 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR10: ISF=0,MUX=5 */
  PORTE_PCR10 = (uint32_t)((PORTE_PCR10 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));
  /* PORTE_PCR11: ISF=0,MUX=5 */
  PORTE_PCR11 = (uint32_t)((PORTE_PCR11 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));
  /* PORTE_PCR12: ISF=0,MUX=5 */
  PORTE_PCR12 = (uint32_t)((PORTE_PCR12 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));
  /* PORTF_PCR17: ISF=0,MUX=5 */
  PORTF_PCR17 = (uint32_t)((PORTF_PCR17 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));
  /* PORTF_PCR18: ISF=0,MUX=5 */
  PORTF_PCR18 = (uint32_t)((PORTF_PCR18 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));
  /* PORTF_PCR19: ISF=0,MUX=5 */
  PORTF_PCR19 = (uint32_t)((PORTF_PCR19 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x02)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x05)
                ));

  /* Blue */
  /* PORTE_PCR0: ISF=0,MUX=5 */
  PORTE_PCR0 = (uint32_t)((PORTE_PCR0 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR1: ISF=0,MUX=5 */
  PORTE_PCR1 = (uint32_t)((PORTE_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR2: ISF=0,MUX=5 */
  PORTE_PCR2 = (uint32_t)((PORTE_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR3: ISF=0,MUX=5 */
  PORTE_PCR3 = (uint32_t)((PORTE_PCR3 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR4: ISF=0,MUX=5 */
  PORTE_PCR4 = (uint32_t)((PORTE_PCR4 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR5: ISF=0,MUX=5 */
  PORTE_PCR5 = (uint32_t)((PORTE_PCR5 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR6: ISF=0,MUX=5 */
  PORTE_PCR6 = (uint32_t)((PORTE_PCR6 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));
  /* PORTE_PCR7: ISF=0,MUX=5 */
  PORTE_PCR7 = (uint32_t)((PORTE_PCR7 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x02)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x05)
               ));

  /* Sync & contrast control */
  /* PORTD_PCR15: ISF=0,MUX=7 */
  PORTD_PCR15 = (uint32_t)((PORTD_PCR15 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTD_PCR14: ISF=0,MUX=7 */
  PORTD_PCR14 = (uint32_t)((PORTD_PCR14 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTD_PCR13: ISF=0,MUX=7 */
  PORTD_PCR13 = (uint32_t)((PORTD_PCR13 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  /* PORTD_PCR11: ISF=0,MUX=7 */
  PORTD_PCR11 = (uint32_t)((PORTD_PCR11 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x07)
                ));
  DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
  DeviceDataPrv->InitState = 0x00U;
  LCDC_PDD_SetClkDiv(LCDC_BASE_PTR, 9);
  LCDC_PDD_SetClkFrac(LCDC_BASE_PTR, 0);
  LCDC_PDD_SetSLCDSrc(LCDC_BASE_PTR, LCDC_PDD_CLKDIV);
  LCDC_PDD_SetClkSrc(LCDC_BASE_PTR, LCDC_PDD_PLL1);
  /* enable clock */
  /* SIM_SCGC3: LCDC=1 */
  SIM_SCGC3 |= SIM_SCGC3_LCDC_MASK;
  LCDC_PDD_SetPixelClockDivider(LCDC_BASE_PTR, 1);
  LCDC_PDD_SetDisplayType(LCDC_BASE_PTR, LCDC_PDD_TFT);
  LCDC_PDD_SetBitsPerPixel(LCDC_BASE_PTR, LCDC_PDD_BPP_24);
  LCDC_PDD_SetImageEndian(LCDC_BASE_PTR, LCDC_PDD_BIG_ENDIAN);
  LCDC_PDD_SetScreenSize(LCDC_BASE_PTR, 20, 240);
  /* Interrupt setting */
  LCDC_PDD_SetFrameInterruptPosition(LCDC_BASE_PTR, LCDC_PDD_INT_END_OF_FRAME);
  LCDC_PDD_SetGWinInterruptPosition(LCDC_BASE_PTR, LCDC_PDD_INT_END_OF_FRAME);
  LCDC_PDD_SelectIntSyn(LCDC_BASE_PTR, LCDC_PDD_LOAD_FROM_MEMORY);
  /* Signal timing and polarity setting */
  LCDC_PDD_SetHorizontalTiming(LCDC_BASE_PTR, 1, 19, 63);
  LCDC_PDD_SetVerticalTiming(LCDC_BASE_PTR, 1, 4, 18);
  LCDC_PDD_SetLP_HSYNCPolarity(LCDC_BASE_PTR, LCDC_PDD_ACTIVE_LOW);
  LCDC_PDD_SetFLM_VSYNCPolarity(LCDC_BASE_PTR, LCDC_PDD_ACTIVE_LOW);
  LCDC_PDD_SetOEPolarity(LCDC_BASE_PTR, LCDC_PDD_ACTIVE_HIGH);
  LCDC_PDD_SetLSCLKDuringSYNC(LCDC_BASE_PTR, LCDC_PDD_ALWAYS_ON);
  /* DMA settings */
  LCDC_PDD_SetupDMA(LCDC_BASE_PTR, LCDC_PDD_DYNAMIC, 4, 96);
  LCDC_PDD_SetupGWinDMA(LCDC_BASE_PTR, LCDC_PDD_DYNAMIC, 4, 96);
  /* Setup HW cursor */
  LCDC_PDD_CursorOperation(LCDC_BASE_PTR, LCDC_PDD_DISABLED);
  LCDC_PDD_SetCursorPosition(LCDC_BASE_PTR, 0, 0);
  LCDC_PDD_SetCursorSize(LCDC_BASE_PTR, 0, 0);
  LCDC_PDD_SetCursorBlinking(LCDC_BASE_PTR, LCDC_PDD_BLINK_DISABLED);
  LCDC_PDD_SetCursorBlinkRate(LCDC_BASE_PTR, 1);
  LCDC_PDD_SetCursorColor(LCDC_BASE_PTR, 0, 0, 0);
  /* Plane settings */
  BitmapInfo.Address = 0x80000000;
  BitmapInfo.Width = (uint16_t)320;
  BitmapInfo.Height = (uint16_t)240;
  BitmapInfo.Format = 0x00U;
  WindowInfo.X = (uint16_t)0;
  WindowInfo.Y = (uint16_t)0;
  WindowInfo.Width = (uint16_t)320;
  WindowInfo.Height = (uint16_t)240;
  (void)LCDC1_SetupBitmap(DeviceDataPrv, LDD_LCDC_PLANE_0, &BitmapInfo);
  (void)LCDC1_SetupWindow(DeviceDataPrv, LDD_LCDC_PLANE_0, &WindowInfo);
  LCDC_PDD_GWinEnable(LCDC_BASE_PTR, LCDC_PDD_GWIN_DISABLED);
  /* Contrast control */
  LCDC_PDD_ContrastControl(LCDC_BASE_PTR, LCDC_PDD_PWM_DISABLED);
  (void)LCDC_PDD_ReadInterruptStatus(LCDC_BASE_PTR); /* Clear interrupt status flags */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_LCDC1_ID,DeviceDataPrv);
  LCDC_PDD_SelfRefreshMode(LCDC_BASE_PTR, LCDC_PDD_SELF_REF_DISABLED); /* Disable LCD self refresh mode */
  LCDC_PDD_EnableLCD(LCDC_BASE_PTR); /* Enable LCD */
  return DeviceDataPrv;                /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  LCDC1_Main (component LCDC_LDD)
*/
/*!
**     @brief
**         This method is available only in polling mode. If interrupt
**         service is disabled this method replaces the RNG interrupt
**         handler. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method. 
*/
/* ===================================================================*/
void LCDC1_Main(LDD_TDeviceData *DeviceDataPtr)
{
  (void)LCDC_PDD_ReadInterruptStatus(LCDC_BASE_PTR); /* Dummy read of Interrupt Status Register to clear flags */
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
}

/*
** ===================================================================
**     Method      :  LCDC1_SetupBitmap (component LCDC_LDD)
*/
/*!
**     @brief
**         This method configures bitmap (virtual page) for selected
**         layer. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method. 
**     @param
**         PlaneID         - Plane specification.
**     @param
**         BitmapInfo      - Pointer to bitmap
**                           information. 
**     @return
**                         - Error code: 
**                           ERR_OK - ok 
**                           ERR_PARAM_INDEX - plane not supported
*/
/* ===================================================================*/
LDD_TError LCDC1_SetupBitmap(LDD_TDeviceData *DeviceDataPtr, LDD_LCDC_TPlaneID PlaneID, LDD_LCDC_TBitmap *BitmapInfo)
{
  LCDC1_TDeviceData *DeviceDataPrv = (LCDC1_TDeviceData *)DeviceDataPtr;
  /* Temporary variables used for computation */
  uint16_t BytesPerLine;
  uint16_t VirtualWdith;
  LDD_TData* addr;

  /* Compute number of bytes required to hold 1 virtual line */
  DeviceDataPrv->BPP = 0x20U; /* for 18 and 24 bits per pixel, 32 bits of memory used */
  BytesPerLine = BitmapInfo->Width * 0x04U;

  /* Compute virtual page width - number of 32bit words required to hold 1 virtual line */
  VirtualWdith = BytesPerLine / 0x04U;
  if ((BytesPerLine % 0x04U) != 0x00U)
  {
    VirtualWdith += 0x01U;
  }

  if ((BitmapInfo->Format & LDD_LCDC_REVERSED_VERTICAL_SCAN) != 0x00U) /* Reversed vertical scan */
  {
    addr = (LDD_TData*)((uint32_t)BitmapInfo->Address + (((uint32_t)VirtualWdith*0x04U)*((uint32_t)BitmapInfo->Height-0x01U)));
  } else {
    addr = BitmapInfo->Address;
  }

  switch (PlaneID) {
    case LDD_LCDC_PLANE_0:
      if ((BitmapInfo->Format & LDD_LCDC_REVERSED_VERTICAL_SCAN) != 0x00U) /* Reversed vertical scan */
      {
        LCDC_PDD_SetScanDir(LCDC_BASE_PTR, LCDC_PDD_REVERSE_DIR);
      } else {
        LCDC_PDD_SetScanDir(LCDC_BASE_PTR, LCDC_PDD_NORMAL_DIR);
      }
      DeviceDataPrv->L0Bitmap = addr;
      DeviceDataPrv->L0BitmapVirtualWidth = VirtualWdith;
      LCDC_PDD_SetVirtualPageWidth(LCDC_BASE_PTR, DeviceDataPrv->L0BitmapVirtualWidth);
      DeviceDataPrv->InitState |= INIT_L0_BITMAP;
      DeviceDataPrv->L0BitmapWidthPx = BitmapInfo->Width;
      DeviceDataPrv->L0BitmapHeightPx = BitmapInfo->Height;
     break;
    case LDD_LCDC_PLANE_1:
      if ((BitmapInfo->Format & LDD_LCDC_REVERSED_VERTICAL_SCAN) != 0x00U) /* Reversed vertical scan */
      {
        LCDC_PDD_SetGWinScanDir(LCDC_BASE_PTR, LCDC_PDD_REVERSE_DIR);
      } else {
        LCDC_PDD_SetGWinScanDir(LCDC_BASE_PTR, LCDC_PDD_NORMAL_DIR);
      }
      DeviceDataPrv->L1Bitmap = addr;
      DeviceDataPrv->L1BitmapVirtualWidth = VirtualWdith;
      LCDC_PDD_SetGWinVirtualPageWidth(LCDC_BASE_PTR, DeviceDataPrv->L1BitmapVirtualWidth);
      DeviceDataPrv->InitState |= INIT_L1_BITMAP;
      DeviceDataPrv->L1BitmapWidthPx = BitmapInfo->Width;
      DeviceDataPrv->L1BitmapHeightPx = BitmapInfo->Height;
     break;
    default:
      return ERR_PARAM_INDEX;
  }
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  LCDC1_SetupWindow (component LCDC_LDD)
*/
/*!
**     @brief
**         This method configures window in bitmap, that will be
**         displayed. 
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method. 
**     @param
**         PlaneID         - Plane specification.
**     @param
**         WindowInfo      - Pointer to window information
**     @return
**                         - Error code: 
**                           ERR_OK - ok 
**                           ERR_PARAM_RANGE - window crosses bitmap
**                           boundary (range checking must be enabled) 
**                           ERR_PARAM_INDEX - plane not supported 
**                           ERR_FAILED - initialization error - call
**                           SetupBitmap() before SetupWindow() for
**                           selected plane
*/
/* ===================================================================*/
LDD_TError LCDC1_SetupWindow(LDD_TDeviceData *DeviceDataPtr, LDD_LCDC_TPlaneID PlaneID, LDD_LCDC_TWindow *WindowInfo)
{
  LCDC1_TDeviceData *DeviceDataPrv = (LCDC1_TDeviceData *)DeviceDataPtr;
  uint32_t addrX; /* computed address adjustment */
  uint32_t addrY;
  uint16_t offset; /* panning offset */
  uint32_t virtualWidth; /* common variables */
  uint32_t bmpHeight;
  uint8_t scanDir;


  switch (PlaneID) {
    case LDD_LCDC_PLANE_0:
      if ((DeviceDataPrv->InitState & INIT_L0_BITMAP) == 0x00U) {
        return ERR_FAILED; /* Bitmap is not initialized. */
      }
      if ((DeviceDataPrv->L0BitmapWidthPx < (WindowInfo->X + WindowInfo->Width)) ||
          (DeviceDataPrv->L0BitmapHeightPx < (WindowInfo->Y + WindowInfo->Height)) ||
          (WindowInfo->Width != (uint16_t)LCD_RES_X) || /* Window size for PLANE_0 must be equal to LCD size */
          (WindowInfo->Height != (uint16_t)LCD_RES_Y))  {
        return ERR_PARAM_RANGE;
      }
      virtualWidth = DeviceDataPrv->L0BitmapVirtualWidth;
      scanDir = LCDC_PDD_GetScanDir(LCDC_BASE_PTR);
      bmpHeight = DeviceDataPrv->L0BitmapHeightPx;
    break;
    case LDD_LCDC_PLANE_1:
      if ((DeviceDataPrv->InitState & INIT_L1_BITMAP) == 0x00U) {
        return ERR_FAILED; /* Bitmap is not initialized. */
      }
      if ((DeviceDataPrv->L1BitmapWidthPx < (WindowInfo->X + WindowInfo->Width)) ||
          (DeviceDataPrv->L1BitmapHeightPx < (WindowInfo->Y + WindowInfo->Height)) ||
          (WindowInfo->Width > (uint16_t)LCD_RES_X) ||
          (WindowInfo->Height > (uint16_t)LCD_RES_Y) ||
          ((WindowInfo->Width % 0x10U) != 0x00U))  {
        return ERR_PARAM_RANGE;
      }
      virtualWidth = DeviceDataPrv->L1BitmapVirtualWidth;
      scanDir = LCDC_PDD_GetGWinScanDir(LCDC_BASE_PTR);
      bmpHeight = DeviceDataPrv->L1BitmapHeightPx;
    break;
    default:
      return ERR_PARAM_INDEX;
  }

  /* Compute starting address of window in virtual bitmap and panning offset */
  addrX = WindowInfo->X*((uint32_t)DeviceDataPrv->BPP / 0x08U);
  if (scanDir == LCDC_PDD_NORMAL_DIR) /* normal vertical scan */
  {
    addrY = WindowInfo->Y * (virtualWidth*0x04U);
  } else { /* reversed vertical scan */
    addrY = ((bmpHeight - WindowInfo->Height) - WindowInfo->Y) * (virtualWidth*0x04U);
  }
  offset = (uint16_t)(((addrY+addrX) % 0x04U) * 0x08U); /* compute panning offset */

  switch (PlaneID) {
    case LDD_LCDC_PLANE_0:
      if (scanDir == LCDC_PDD_NORMAL_DIR) /* normal vertical scan */
      {
        LCDC_PDD_SetScreenStartAddress(LCDC_BASE_PTR, ((uint32_t)DeviceDataPrv->L0Bitmap + addrY + addrX) & 0xFFFFFFFCU);
      } else { /* reversed vertical scan */
        LCDC_PDD_SetScreenStartAddress(LCDC_BASE_PTR, (((uint32_t)DeviceDataPrv->L0Bitmap - addrY) + addrX) & 0xFFFFFFFCU);
      }
      LCDC_PDD_SetPanningOffset(LCDC_BASE_PTR, offset);
      DeviceDataPrv->InitState |= INIT_L0_WINDOW;
      DeviceDataPrv->L0WindowWidthPx = WindowInfo->Width;
      DeviceDataPrv->L0WindowHeightPx = WindowInfo->Height;
      break;
    case LDD_LCDC_PLANE_1:
      if (scanDir == LCDC_PDD_NORMAL_DIR) /* normal vertical scan */
      {
        LCDC_PDD_SetGWinStartAddress(LCDC_BASE_PTR, ((uint32_t)DeviceDataPrv->L1Bitmap + addrY + addrX) & 0xFFFFFFFCU);
      } else { /* reversed vertical scan */
        LCDC_PDD_SetGWinStartAddress(LCDC_BASE_PTR, (((uint32_t)DeviceDataPrv->L1Bitmap - addrY) + addrX) & 0xFFFFFFFCU);
      }
      LCDC_PDD_SetGWinSize(LCDC_BASE_PTR, (uint32_t)WindowInfo->Width/0x10U, WindowInfo->Height);
      LCDC_PDD_SetGWinPanningOffset(LCDC_BASE_PTR, offset);
      LCDC_PDD_GWinEnable(LCDC_BASE_PTR, LCDC_PDD_GWIN_ENABLED);
      DeviceDataPrv->InitState |= INIT_L1_WINDOW;
      DeviceDataPrv->L1WindowWidthPx = WindowInfo->Width;
      DeviceDataPrv->L1WindowHeightPx = WindowInfo->Height;
     break;
    default:
      return ERR_PARAM_INDEX;     
  }

  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  LCDC1_SetupWindowPosOnScreen (component LCDC_LDD)
*/
/*!
**     @brief
**         This method configures window position on the screen.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by Init method. 
**     @param
**         PlaneID         - Plane specification.
**     @param
**         X               - Window position on the screen - X
**     @param
**         Y               - Window position on the screen - Y
**     @return
**                         - Error code: 
**                           ERR_OK - ok 
**                           ERR_PARAM_INDEX - plane not supported 
**                           ERR_PARAM_RANGE - window position is out of
**                           range (range checking optimalization must
**                           be enabled) 
**                           ERR_FAILED - initialization error - call
**                           SetupBitmap and SetupWindow before
**                           SetupWindowPosOnScreen()
*/
/* ===================================================================*/
LDD_TError LCDC1_SetupWindowPosOnScreen(LDD_TDeviceData *DeviceDataPtr, LDD_LCDC_TPlaneID PlaneID, uint16_t X, uint16_t Y)
{
  LCDC1_TDeviceData *DeviceDataPrv = (LCDC1_TDeviceData *)DeviceDataPtr;

  if (PlaneID == LDD_LCDC_PLANE_1)
  {
    if ((DeviceDataPrv->InitState & INIT_L1_DONE) != INIT_L1_DONE) {
      return ERR_FAILED; /* Window and/or bitmap is not initialized*/
    }
    if (((DeviceDataPrv->L1WindowWidthPx + X) > (uint16_t)LCD_RES_X) ||
        ((DeviceDataPrv->L1WindowHeightPx + Y) > (uint16_t)LCD_RES_Y)) {
      return ERR_RANGE;
    }
    LCDC_PDD_SetGWinPosition(LCDC_BASE_PTR, X, Y);
  } else {
    return ERR_PARAM_INDEX;
  }

  return ERR_OK;
}

/* END LCDC1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
