
/**
 * @file   DrvFlexBus.h
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Definitions for driver for the MK70 flex bus controller
 *
 * Contains all required definitions for the MK70 flex bus controller
 */

#ifndef DRV_FLEXBUS_H
#define DRV_FLEXBUS_H

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "IO_Map.h"
#include "DrvTypeDefs.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////
                                       
#define FB_PORT1_SFR    PORTD_BASE_PTR //!< Flexbus I/O port SFR
#define FB_PORT2_SFR    PORTC_BASE_PTR //!< Flexbus I/O port SFR
#define FB_PORT3_SFR    PORTB_BASE_PTR //!< Flexbus I/O port SFR
#define FB_PORT4_SFR    PORTA_BASE_PTR //!< Flexbus I/O port SFR

#define FB_PORT1        PTD_BASE_PTR   //!< Flexbus I/O port
#define FB_PORT2        PTC_BASE_PTR   //!< Flexbus I/O port
#define FB_PORT3        PTB_BASE_PTR   //!< Flexbus I/O port
#define FB_PORT4        PTA_BASE_PTR   //!< Flexbus I/O port

#define FB_ALE_BIT      0              //!< Flexbus ALE I/O bit
#define FB_CS0_BIT      1              //!< Flexbus CS0 I/O bit
#define FB_OE_BIT       19             //!< Flexbus OE I/O bit
#define FB_RW_BIT       11             //!< Flexbus RW I/O bit

#define FB_A1_BIT       5              //!< Flexbus address line A1 I/O bit
#define FB_A2_BIT       4              //!< Flexbus address line A2 I/O bit
#define FB_A3_BIT       3              //!< Flexbus address line A3 I/O bit
#define FB_A4_BIT       2              //!< Flexbus address line A4 I/O bit
#define FB_A5_BIT       10             //!< Flexbus address line A5 I/O bit
#define FB_A6_BIT       9              //!< Flexbus address line A6 I/O bit
#define FB_A7_BIT       8              //!< Flexbus address line A7 I/O bit
#define FB_A8_BIT       7              //!< Flexbus address line A8 I/O bit
#define FB_A9_BIT       6              //!< Flexbus address line A9 I/O bit
#define FB_A10_BIT      5              //!< Flexbus address line A10 I/O bit
#define FB_A11_BIT      4              //!< Flexbus address line A11 I/O bit
#define FB_A12_BIT      2              //!< Flexbus address line A12 I/O bit
#define FB_A13_BIT      1              //!< Flexbus address line A13 I/O bit
#define FB_A14_BIT      0              //!< Flexbus address line A14 I/O bit
#define FB_A15_BIT      18             //!< Flexbus address line A15 I/O bit
#define FB_A16_BIT      17             //!< Flexbus address line A16/D0 I/O bit
#define FB_A17_BIT      16             //!< Flexbus address line A17/D1 I/O bit
#define FB_A18_BIT      11             //!< Flexbus address line A18/D2 I/O bit
#define FB_A19_BIT      10             //!< Flexbus address line A19/D3 I/O bit
#define FB_A20_BIT      9              //!< Flexbus address line A20/D4 I/O bit
#define FB_A21_BIT      8              //!< Flexbus address line A21/D5 I/O bit
#define FB_A22_BIT      7              //!< Flexbus address line A22/D6 I/O bit
#define FB_A23_BIT      6              //!< Flexbus address line A23/D7 I/O bit
#define FB_A24_BIT      28             //!< Flexbus address line A24 I/O bit

#define FB_D24_BIT      15             //!< Flexbus address line D8 I/O bit
#define FB_D25_BIT      14             //!< Flexbus address line D9 I/O bit
#define FB_D26_BIT      13             //!< Flexbus address line D10 I/O bit
#define FB_D27_BIT      12             //!< Flexbus address line D11 I/O bit
#define FB_D28_BIT      23             //!< Flexbus address line D12 I/O bit
#define FB_D29_BIT      22             //!< Flexbus address line D13 I/O bit
#define FB_D30_BIT      21             //!< Flexbus address line D14 I/O bit
#define FB_D31_BIT      20             //!< Flexbus address line D15 I/O bit

#define FB_CLK_OUT_BIT  3

#define FB_BASE_ADDRESS 0x60000000     //!< Flexbus memory base address
#define FB_BLOCK_SIZE   0x00400000     //!< Flexbus memory block size, 4Meg
#define FB_WAIT_STATES  4              //!< Flexbus memory wait states, set for slowest memory

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

const CHAR* DrvFlexBusGetVersion(void);
void DrvFlexBusInit( void );

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif
