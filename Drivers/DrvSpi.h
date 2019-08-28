
/**
 * @file   DrvSpi.h
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Definitions for driver for the SPI chip selects
 *
 * Contains the SPI chip selects definitions
 */

#ifndef _DRV_SPI_H_
#define _DRV_SPI_H_

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "PE_Types.h"
#include "IO_Map.h"

////////////////////////////////////////////////////////////////////////////////
//
// Type definitions.
//
////////////////////////////////////////////////////////////////////////////////

//Id definitions for the available SPI devices.
typedef enum {
   SPI_DEVICE_NONE      = 0x00,
   SPI_DEVICE_FLASH     = 0x01,
   SPI_DEVICE_EXT_ADC   = 0x02,
   SPI_DEVICE_EEPROM    = 0x03,  
   SPI_DEVICE_RTC       = 0x04,
   SPI_DEVICE_MMC       = 0x05,
   SPI_DEVICE_ADC       = 0x06,
   SPI_DEVICE_DAC       = 0x07,
   SPI_DEVICE_TEMP      = 0x08,
   SPI_DEVICE_LCD       = 0x09,
   SPI_DEVICE_EXTERNAL  = 0x0A,
   SPI_DEVICE_ALL       = 0xFF 
}_SpiDevice;

////////////////////////////////////////////////////////////////////////////////
//
// Definitions.
//
////////////////////////////////////////////////////////////////////////////////

#define FLASH_CS_IO_PORT   PTA_BASE_PTR //! Serial flash chip select bit port register
#define FLASH_CS_IO_SFR    PORTA_BASE_PTR //! Serial flash chip select bit special function register
#define FLASH_CS0_IO_BIT   14          //!< Serial flash chip I/O port bit
#define FLASH_CS1_IO_BIT   0 /* Not supported for MK70? */


                                       //! SSP port register
#define SPI_EXT_CS_PORT             PTA_BASE_PTR
                                       //! SSP port special function register
#define SPI_EXT_CS_PORT_SFR         PORTA_BASE_PTR                    
#define SPI_EXT_CS_BIT              13 //!< SSP spare chip select

////////////////////////////////////////////////////////////////////////////////
//
// Macro's
//
////////////////////////////////////////////////////////////////////////////////

                                       //! External SPI chip select eanbled
#define DrvSpiExtCsEnabled()     (SPI_EXT_CS_PORT->PCOR = (0x00000001 << SPI_EXT_CS_BIT))
                                       //! External SPI chip select disabled
#define DrvSpiExtCsDisabled()    (SPI_EXT_CS_PORT->PCOR = (0x00000001 << SPI_EXT_CS_BIT))

#define DrvFlashCsHigh()         (FLASH_CS_IO_PORT->PSOR = (0x00000001 << FLASH_CS0_IO_BIT)) //! Serial flash chip select inactive macro
#define DrvFlashDisable()              DrvFlashCsHigh() //! Serial flash chip select inactive macro

////////////////////////////////////////////////////////////////////////////////
//
// Function prototypes.
//
////////////////////////////////////////////////////////////////////////////////

const char* DrvSpiGetVersion(void);
void DrvSpiInit(void);
void DrvSpiSelectDevice( _SpiDevice Device );

////////////////////////////////////////////////////////////////////////////////
//
// End of include file.
//
////////////////////////////////////////////////////////////////////////////////

#endif

