
/**
 * @file   DrvFlexBus.c
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Driver for the MK70 flex bus controller.
 *
 * Contains the initialization routine for the MK70 flex bus controller
 */

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include <DrvTypeDefs.h>
#include "IO_Map.h"

#include <DrvIOPort.h>
#include <DrvFlexBus.h>

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

#if (DRV_LIB_REV == 1000)
const CHAR DrvFlexBusVersion[] = "1.0.0.0";
#else
const CHAR DrvFlexBusVersion[] = "2.0.0.0";
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

////////////////////////////////////////////////////////////////////////////////
//
// Global functions.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @name    DrvFlexBusGetVersion
 * @brief   Reports the flex bus driver verison
 * @ingroup Drivers
 *
 * This function returns flex bus driver version
 *
 * @param None 
 *
 * @retval const CHAR* -> version string
 *
 * Example Usage:
 * @code
 *    string = DrvFlexBusGetVersion();
 * @endcode
 */

const CHAR* DrvFlexBusGetVersion(void)
{
   return(DrvFlexBusVersion);
}

/**
 * @name    DrvFlexBusInit
 * @brief   Initializes flex bus
 * @ingroup Drivers
 *
 * This function initializes the flex bus chip select, address lines, data lines and 
 * control lines. Bus configuration...
 * * 16 bit mulitpled data bus 
 * * Base address 0xA0000000
 * * 4MB address space [0x00400000]
 * * 4 wait states
 * * auto-completion  
 *
 * @param None 
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvFlexBusInit(); 
 * @endcode
 */

void DrvFlexBusInit( void )
{
   SIM_SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
   SIM_SOPT2 |= SIM_SOPT2_FBSL_MASK;
   FB_CSAR0 = FB_CSAR_BA(((UINT32)FB_BASE_ADDRESS >> FB_CSAR_BA_SHIFT));
   FB_CSCR0 = (FB_CSCR_SWS(0) | FB_CSCR_ASET(0x03) | FB_CSCR_RDAH(0x03) | FB_CSCR_WRAH(0x03) | 
               FB_CSCR_WS(FB_WAIT_STATES) | FB_CSCR_AA_MASK | FB_CSCR_PS(2));
   FB_CSMR0 = FB_CSMR_BAM(((UINT32)FB_BLOCK_SIZE - 1) >> FB_CSMR_BAM_SHIFT) | FB_CSMR_V_MASK;

   DrvIOSetPortParFunction(FB_PORT1_SFR, FB_ALE_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT1_SFR, FB_CS0_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_OE_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_RW_BIT, IO_PORT_PIN_IO_FUNCTION5);

   DrvIOSetPortParFunction(FB_PORT1_SFR, FB_A1_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT1_SFR, FB_A2_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT1_SFR, FB_A3_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT1_SFR, FB_A4_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A5_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A6_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A7_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A8_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A9_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A10_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A11_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A12_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A13_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_A14_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A15_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A16_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A17_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A18_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A19_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A20_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A21_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A22_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_A23_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT4_SFR, FB_A24_BIT, IO_PORT_PIN_IO_FUNCTION5);

   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_D24_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_D25_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_D26_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_D27_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_D28_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_D29_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_D30_BIT, IO_PORT_PIN_IO_FUNCTION5);
   DrvIOSetPortParFunction(FB_PORT3_SFR, FB_D31_BIT, IO_PORT_PIN_IO_FUNCTION5);
#ifdef FB_CLK_OUT
   DrvIOSetPortParFunction(FB_PORT2_SFR, FB_CLK_OUT_BIT, IO_PORT_PIN_IO_FUNCTION5);
#endif
   DrvIOSetPortPinDirection(FB_PORT1, FB_CS0_BIT, IO_PORT_DDR_OUTPUT);
}
