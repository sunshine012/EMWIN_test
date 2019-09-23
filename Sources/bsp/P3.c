/**HEADER********************************************************************
 *
 * Copyright (c) 2010 Freescale Semiconductor;
 * All Rights Reserved
 *
 ***************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************
 *
 * $FileName: P2.c$
 * $Version :
 * $Date    :
 *
 * Comments:
 *
 *   This file contains board-specific initialization functions.
 *
 *END************************************************************************/
#include "usb_bsp.h"
#include "derivative.h"
#include "user_config.h"

#if (defined MCU_MK60N512VMD100) || (defined MCU_MK53N512CMD100)
#define BSP_CLOCK_SRC                   (50000000ul)       // crystal, oscillator freq
#else
#define BSP_CLOCK_SRC                   (8000000ul)       // crystal, oscillator freq
#endif
#define BSP_REF_CLOCK_SRC               (2000000ul)       // must be 2-4MHz

#define BSP_CORE_DIV                    (1)
#define BSP_BUS_DIV                     (1)
#define BSP_FLEXBUS_DIV                 (1)
#define BSP_FLASH_DIV                   (2)

// BSP_CLOCK_MUL from interval 24 - 55
#define BSP_CLOCK_MUL                   (24)    // 48MHz

#define BSP_REF_CLOCK_DIV               (BSP_CLOCK_SRC / BSP_REF_CLOCK_SRC)

#define BSP_CLOCK                       (BSP_REF_CLOCK_SRC * BSP_CLOCK_MUL)
#define BSP_CORE_CLOCK                  (BSP_CLOCK / BSP_CORE_DIV)          // CORE CLK, max 100MHz
#define BSP_SYSTEM_CLOCK                (BSP_CORE_CLOCK)                    // SYSTEM CLK, max 100MHz
#define BSP_BUS_CLOCK                   (BSP_CLOCK / BSP_BUS_DIV)       // max 50MHz
#define BSP_FLEXBUS_CLOCK               (BSP_CLOCK / BSP_FLEXBUS_DIV)
#define BSP_FLASH_CLOCK                 (BSP_CLOCK / BSP_FLASH_DIV)     // max 25MHz


#ifdef MCU_MK70F12
enum usbhs_clock
{
	MCGPLL0,
	MCGPLL1,
	MCGFLL,
	PLL1,
	CLKIN
};

// Constants for use in pll_init
#define NO_OSCINIT 0
#define OSCINIT 1

#define OSC_0 0
#define OSC_1 1

#define LOW_POWER 0
#define HIGH_GAIN 1

#define CANNED_OSC  0
#define CRYSTAL 1

#define PLL_0 0
#define PLL_1 1

#define PLL_ONLY 0
#define MCGOUT 1

// MCG Mode defines
/*
#define FEI  1
#define FEE  2
#define FBI  3
#define FBE  4
#define BLPI 5
#define BLPE 6
#define PBE  7
#define PEE  8
 */

#define BLPI 1
#define FBI  2
#define FEI  3
#define FEE  4
#define FBE  5
#define BLPE 6
#define PBE  7
#define PEE  8

// IRC defines
#define SLOW_IRC 0
#define FAST_IRC 1

/*
 * Input Clock Info
 */
#define CLK0_FREQ_HZ        50000000
#define CLK0_TYPE           CANNED_OSC

#define CLK1_FREQ_HZ        12000000
#define CLK1_TYPE           CRYSTAL

/* Select Clock source */
/* USBHS Fractional Divider value for 120MHz input */
/* USBHS Clock = PLL0 x (USBHSFRAC+1) / (USBHSDIV+1)       */
#define USBHS_FRAC    0
#define USBHS_DIV     SIM_CLKDIV2_USBHSDIV(1)
#define USBHS_CLOCK   MCGPLL0


/* USB Fractional Divider value for 120MHz input */
/** USB Clock = PLL0 x (FRAC +1) / (DIV+1)       */
/** USB Clock = 120MHz x (1+1) / (4+1) = 48 MHz    */
#define USB_FRAC    SIM_CLKDIV2_USBFSFRAC_MASK
#define USB_DIV     SIM_CLKDIV2_USBFSDIV(4)


/* Select Clock source */
#define USB_CLOCK   MCGPLL0
//#define USB_CLOCK   MCGPLL1
//#define USB_CLOCK   MCGFLL
//#define USB_CLOCK   PLL1
//#define USB_CLOCK   CLKIN

/* The expected PLL output frequency is:
 * PLL out = (((CLKIN/PRDIV) x VDIV) / 2)
 * where the CLKIN can be either CLK0_FREQ_HZ or CLK1_FREQ_HZ.
 * 
 * For more info on PLL initialization refer to the mcg driver files.
 */

#define PLL0_PRDIV      5
#define PLL0_VDIV       24

#define PLL1_PRDIV      5
#define PLL1_VDIV       30
#endif

extern uint_32 ___VECTOR_RAM[];

/*****************************************************************************
 * Local Variables
 *****************************************************************************/
#ifdef MCU_MK70F12
int mcg_clk_hz;
int mcg_clk_khz;
int core_clk_khz;
int periph_clk_khz;
int pll_0_clk_khz;
int pll_1_clk_khz;
#endif

/***************************************************************************
 * Local Functions
 ***************************************************************************/
#ifdef MCU_MK70F12
void trace_clk_init(void);
void fb_clk_init(void);
#endif

/***************************************************************************
 * Local Functions
 ***************************************************************************/
#if HIGH_SPEED_DEVICE
void ULPI_Init();
#endif

/*****************************************************************************
 * @name     wdog_disable
 *
 * @brief:   Disable watchdog.
 *
 * @param  : None
 *
 * @return : None
 *****************************************************************************
 * It will disable watchdog.
 ****************************************************************************/
static void wdog_disable(void)
{
	/* Write 0xC520 to the unlock register */
	WDOG_UNLOCK = 0xC520;

	/* Followed by 0xD928 to complete the unlock */
	WDOG_UNLOCK = 0xD928;

	/* Clear the WDOGEN bit to disable the watchdog */
	WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}

/*****************************************************************************
 * @name     pll_init
 *
 * @brief:   Initialization of the MCU.
 *
 * @param  : None
 *
 * @return : None
 *****************************************************************************
 * It will configure the MCU to disable STOP and COP Modules.
 * It also set the MCG configuration and bus clock frequency.
 ****************************************************************************/
static unsigned int pll_init(
#ifdef MCU_MK70F12
		unsigned char init_osc, 
		unsigned char osc_select, 
		int crystal_val, 
		unsigned char hgo_val, 
		unsigned char erefs_val, 
		unsigned char pll_select, 
		signed char prdiv_val, 
		signed char vdiv_val, 
		unsigned char mcgout_select
#endif
)
{
	return 0;
}
 //pll_init

/***************************************************************************
 * Global Functions
 ***************************************************************************/

/*FUNCTION*-------------------------------------------------------------------
 *
 * Function Name    : _bsp_platform_init
 * Returned Value   : 0 for success
 * Comments         :
 *    This function performs BSP-specific related to the MCF51JM platform
 *
 *END*----------------------------------------------------------------------*/
void _bsp_platform_init(void)
{
	/* Point the VTOR to the new copy of the vector table */
	SCB_VTOR = (uint_32)___VECTOR_RAM;

#if !HIGH_SPEED_DEVICE
	NVICICPR2 = (1 << 9);                     //Clear any pending interrupts on USB
	NVICISER2 = (1 << 9);                     //Enable interrupts from USB module
#endif

#ifndef MCU_MK70F12
	/* init pll */
	pll_init();

	/* SIM Configuration */
	MPU_CESR=0;

	SIM_SCGC4|=(SIM_SCGC4_USBOTG_MASK);             // USB Clock Gating

	// PLL/FLL selected as CLK source
	SIM_SOPT2 |= SIM_SOPT2_USBSRC_MASK | SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_CLKDIV2=0x02;                               // USB Freq Divider

	// weak pulldowns
	USB0_USBCTRL=0x40;
#else
	// K70 initialization
	/*
	 * Enable all of the port clocks. These have to be enabled to configure
	 * pin muxing options, so most code will need all of these on anyway.
	 */
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
			| SIM_SCGC5_PORTB_MASK
			| SIM_SCGC5_PORTC_MASK
			| SIM_SCGC5_PORTD_MASK
			| SIM_SCGC5_PORTE_MASK 
			| SIM_SCGC5_PORTF_MASK );

	// releases hold with ACKISO:  Only has an effect if recovering from VLLS1, VLLS2, or VLLS3
	// if ACKISO is set you must clear ackiso before calling pll_init 
	//    or pll init hangs waiting for OSC to initialize
	// if osc enabled in low power modes - enable it first before ack
	// if I/O needs to be maintained without glitches enable outputs and modules first before ack.
	if (PMC_REGSC &  PMC_REGSC_ACKISO_MASK)
		PMC_REGSC |= PMC_REGSC_ACKISO_MASK;

#if defined(NO_PLL_INIT)
	mcg_clk_hz = 21000000; //FEI mode
#elif defined (ASYNCH_MODE)  
	/* Set the system dividers */
	/* NOTE: The PLL init will not configure the system clock dividers,
	 * so they must be configured appropriately before calling the PLL
	 * init function to ensure that clocks remain in valid ranges.
	 */  
	SIM_CLKDIV1 = ( 0
			| SIM_CLKDIV1_OUTDIV1(0)
			| SIM_CLKDIV1_OUTDIV2(1)
			| SIM_CLKDIV1_OUTDIV3(1)
			| SIM_CLKDIV1_OUTDIV4(5) );

	/* Initialize PLL0 */
	/* PLL0 will be the source for MCG CLKOUT so the core, system, FlexBus, and flash clocks are derived from it */ 
	mcg_clk_hz = pll_init(OSCINIT,   /* Initialize the oscillator circuit */
			OSC_0,     /* Use CLKIN0 as the input clock */
			CLK0_FREQ_HZ,  /* CLKIN0 frequency */
			LOW_POWER,     /* Set the oscillator for low power mode */
			CLK0_TYPE,     /* Crystal or canned oscillator clock input */
			PLL_0,         /* PLL to initialize, in this case PLL0 */
			PLL0_PRDIV,    /* PLL predivider value */
			PLL0_VDIV,     /* PLL multiplier */
			MCGOUT);       /* Use the output from this PLL as the MCGOUT */

	/* Check the value returned from pll_init() to make sure there wasn't an error */
	if (mcg_clk_hz < 0x100)
		while(1);

	/* Initialize PLL1 */
	/* PLL1 will be the source for the DDR controller, but NOT the MCGOUT */   
	pll_1_clk_khz = (pll_init(NO_OSCINIT, /* Don't init the osc circuit, already done */
			OSC_0,      /* Use CLKIN0 as the input clock */
			CLK0_FREQ_HZ,  /* CLKIN0 frequency */
			LOW_POWER,     /* Set the oscillator for low power mode */
			CLK0_TYPE,     /* Crystal or canned oscillator clock input */
			PLL_1,         /* PLL to initialize, in this case PLL1 */
			PLL1_PRDIV,    /* PLL predivider value */
			PLL1_VDIV,     /* PLL multiplier */
			PLL_ONLY) / 1000);   /* Don't use the output from this PLL as the MCGOUT */

	/* Check the value returned from pll_init() to make sure there wasn't an error */
	if ((pll_1_clk_khz * 1000) < 0x100)
		while(1);

	pll_0_clk_khz = mcg_clk_hz / 1000;       

#elif defined (SYNCH_MODE)  
	/* Set the system dividers */
	/* NOTE: The PLL init will not configure the system clock dividers,
	 * so they must be configured appropriately before calling the PLL
	 * init function to ensure that clocks remain in valid ranges.
	 */  
	SIM_CLKDIV1 = ( 0
			| SIM_CLKDIV1_OUTDIV1(0)
			| SIM_CLKDIV1_OUTDIV2(2)
			| SIM_CLKDIV1_OUTDIV3(2)
			| SIM_CLKDIV1_OUTDIV4(5) );

	/* Initialize PLL1 */
	/* PLL1 will be the source MCGOUT and the DDR controller */   
	mcg_clk_hz = pll_init(OSCINIT, /* Don't init the osc circuit, already done */
			OSC_0,      /* Use CLKIN0 as the input clock */
			CLK0_FREQ_HZ,  /* CLKIN0 frequency */
			LOW_POWER,     /* Set the oscillator for low power mode */
			CLK0_TYPE,     /* Crystal or canned oscillator clock input */
			PLL_1,         /* PLL to initialize, in this case PLL1 */
			PLL1_PRDIV,    /* PLL predivider value */
			PLL1_VDIV,     /* PLL multiplier */
			MCGOUT);   /* Don't use the output from this PLL as the MCGOUT */

	/* Check the value returned from pll_init() to make sure there wasn't an error */
	if (mcg_clk_hz < 0x100)
		while(1);

	/* Initialize PLL0 */
	/* PLL0 is initialized, but not used as the MCGOUT */ 
	pll_0_clk_khz = (pll_init(NO_OSCINIT,   /* Initialize the oscillator circuit */
			OSC_0,     /* Use CLKIN0 as the input clock */
			CLK0_FREQ_HZ,  /* CLKIN0 frequency */
			LOW_POWER,     /* Set the oscillator for low power mode */
			CLK0_TYPE,     /* Crystal or canned oscillator clock input */
			PLL_0,         /* PLL to initialize, in this case PLL0 */
			PLL0_PRDIV,    /* PLL predivider value */
			PLL0_VDIV,     /* PLL multiplier */
			PLL_ONLY) / 1000);       /* Use the output from this PLL as the MCGOUT */

	/* Check the value returned from pll_init() to make sure there wasn't an error */
	if ((pll_0_clk_khz * 1000) < 0x100)
		while(1);

	pll_1_clk_khz = mcg_clk_hz / 1000;       

#else
#error "A PLL configuration for this platform is NOT defined"
#endif


	/*
	 * Use the value obtained from the pll_init function to define variables
	 * for the core clock in kHz and also the peripheral clock. These
	 * variables can be used by other functions that need awareness of the
	 * system frequency.
	 */
	mcg_clk_khz = mcg_clk_hz / 1000;
	core_clk_khz = mcg_clk_khz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV1_MASK) >> 28)+ 1);
	periph_clk_khz = mcg_clk_khz / (((SIM_CLKDIV1 & SIM_CLKDIV1_OUTDIV2_MASK) >> 24)+ 1);

	/* For debugging purposes, enable the trace clock and/or FB_CLK so that
	 * we'll be able to monitor clocks and know the PLL is at the frequency
	 * that we expect.
	 */
	trace_clk_init();
	fb_clk_init();

	/* Initialize the DDR if the project option if defined */
#ifdef DDR_INIT
	twr_ddr2_script_init();
#endif

#if !HIGH_SPEED_DEVICE
	// USB Module
	/* MPU Configuration */
	MPU_CESR=0;	// MPU is disabled. All accesses from all bus masters are allowed

	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL(1)       /** PLL0 reference */   
    	            						  |  SIM_SOPT2_USBFSRC(0)         /** MCGPLLCLK as CLKC source */
    	            						  |  SIM_SOPT2_USBF_CLKSEL_MASK;  /** USB fractional divider like USB reference clock */  
	SIM_CLKDIV2 = USB_FRAC | USB_DIV;         /** Divide reference clock to obtain 48MHz */

	/* Enable USB-OTG IP clocking */
	SIM_SCGC4 |= SIM_SCGC4_USBFS_MASK; 
#endif
#endif
}

/*FUNCTION*-------------------------------------------------------------------
 *
 * Function Name    : _bsp_usb_host_init
 * Returned Value   : 0 for success
 * Comments         :
 *    This function performs BSP-specific initialization related to USB host
 *
 *END*----------------------------------------------------------------------*/
int_32 _bsp_usb_host_init(pointer param){
#if HIGH_SPEED_DEVICE
	ULPI_Init();
#endif
	return 0;
}

#ifdef MCU_MK70F12
/********************************************************************/
void trace_clk_init(void)
{
	/* Set the trace clock to the core clock frequency */
	SIM_SOPT2 |= SIM_SOPT2_TRACECLKSEL_MASK;

	/* Enable the TRACE_CLKOUT pin function on PTF23 (alt6 function) */
	PORTF_PCR23 = ( PORT_PCR_MUX(0x6));
}

/********************************************************************/
void fb_clk_init(void)
{
	/* Enable the clock to the FlexBus module */
	SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;

	/* Enable the FB_CLKOUT function on PTC3 (alt5 function) */
	PORTC_PCR3 = ( PORT_PCR_MUX(0x5));
}

#if HIGH_SPEED_DEVICE
void ULPI_Init(){
	/* Disable the MPU so that USB can access RAM */
	MPU_CESR &= ~MPU_CESR_VLD_MASK;

	/* clock init */
	SIM_CLKDIV2 |= USBHS_FRAC | 
			USBHS_DIV;			// Divide reference clock to obtain 60MHz

	// MCGPLLCLK for the USB 60MHz CLKC source 
	SIM_SOPT2 |= SIM_SOPT2_USBHSRC(1);

	// External 60MHz UPLI Clock
	SIM_SOPT2 |= SIM_SOPT2_USBH_CLKSEL_MASK;

	// enable USBHS clock
	SIM_SCGC6 |= SIM_SCGC6_USB2OTG_MASK;

	// select alternate function 2 for ULPI pins
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA_PCR7 = PORT_PCR_MUX(2);	// DIR
	PORTA_PCR8 = PORT_PCR_MUX(2);	// NXT
	PORTA_PCR10 = PORT_PCR_MUX(2);  // Data0
	PORTA_PCR11 = PORT_PCR_MUX(2);  // Data1
	PORTA_PCR24 = PORT_PCR_MUX(2);	// Data2
	PORTA_PCR25 = PORT_PCR_MUX(2);	// Data3
	PORTA_PCR26 = PORT_PCR_MUX(2);	// Data4
	PORTA_PCR27 = PORT_PCR_MUX(2);	// Data5
	PORTA_PCR28 = PORT_PCR_MUX(2);	// Data6
	PORTA_PCR29 = PORT_PCR_MUX(2);	// Data7
	PORTA_PCR6 = PORT_PCR_MUX(2);	// CLK
	PORTA_PCR9 = PORT_PCR_MUX(2);	// STP

	while(!(USBHS_ULPI_VIEWPORT & USBHS_ULPI_VIEWPORT_ULPI_SS_MASK));

	USBHS_ULPI_VIEWPORT = 0x40000000;
	while(USBHS_ULPI_VIEWPORT & (0x40000000));
#warning "Sometimes, ULPI module doesn't initialize correctly, in debug mode"

#ifdef SERIAL_DEBUG
	printf("module initialized ok\n");
#endif

	// reset module
	USBHS_USBCMD |= USBHS_USBCMD_RST_MASK;

	// wait for reset to complete
	while(USBHS_USBCMD & USBHS_USBCMD_RST_MASK);

#define USBHS_IRQ  (112-16)
	NVICICPR3 = (1 << (USBHS_IRQ % 32));	// Clear any pending interrupts on USBHS 
	NVICISER3 = (1 << (USBHS_IRQ % 32));	// Enable interrupts on USBHS
	NVICICPR3 = (1 << (USBHS_IRQ % 32));	// Clear any pending interrupts on USBHS 
}
#endif // HIGH_SPEED_DEVICE

#endif // MCU_MK70F12
