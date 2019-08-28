
/**
 * @file   DrvSpi.c
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Driver for the SPI chip select selection
 *
 * Contains the SPI chip select initialization and SPI chip select selectio
 */

/*******************************************************************************
 *
 * Platform:      184-000272
 * Module:        Drivers
 * File:          DrvSpi.c
 *
 * Designed by:   Michael Swanson
 *
 * $Workfile: DrvSpi.c $Archive: 
 * $History:
 * 
 * Description:
 *
 * This file implements the driver functions for the SPI
 * 
 *
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include "DrvIOPort.h"
#include "DrvSsp.h"
//#include "DrvFlash_M25PXX.h"
#include "DrvSpi.h"

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

const  char DrvSpiVersion[] = "1.0.0.0";

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
 * @name    DrvSpiGetVersion
 * @brief   Reports the SPI chip select driver verison
 * @ingroup Drivers
 *
 * This function returns SPI chip select driver version
 *
 * @param None 
 *
 * @retval const char* -> version string
 *
 * Example Usage:
 * @code
 *    string = DrvSpiGetVersion();
 * @endcode
 */

const char* DrvSpiGetVersion(void)
{
   return(DrvSpiVersion);
}

/**
 * @name    DrvSpiInit
 * @brief   Initializes external SPI device chip select
 * @ingroup Drivers
 *
 * This function initializes external SPI device chip select
 * @param None
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvSpiInit();
 * @endcode
 */
void DrvSpiInit(void)
{
   DrvSpiExtCsDisabled();              //initialize SPI chip select
   DrvIOSetPortPinDirection(SPI_PORT, SPI_EXT_CS_BIT, IO_PORT_DDR_OUTPUT);
   DrvIOSetPortParFunction(SPI_PORT_SFR, SPI_EXT_CS_BIT, IO_PORT_PIN_IO_GPIO);
   DrvSpiSelectDevice(SPI_DEVICE_NONE);
}

/**
 * @name    DrvSpiSelectDevice
 * @brief   Selects SPI device
 * @ingroup Drivers
 *
 * This function selects the passed SPI device.
 * @param _SpiDevice
 * * SPI_DEVICE_NONE   
 * * SPI_DEVICE_FLASH 
 * * SPI_DEVICE_EXT_ADC
 * * SPI_DEVICE_EEPROM 
 * * SPI_DEVICE_RTC    
 * * SPI_DEVICE_MMC    
 * * SPI_DEVICE_ADC    
 * * SPI_DEVICE_DAC    
 * * SPI_DEVICE_TEMP   
 * * SPI_DEVICE_LCD    
 *
 * @retval void 
 *
 * Example Usage:
 * @code
 *    DrvSpiSelectDevice(SPI_DEVICE_FLASH);
 * @endcode
 */

void DrvSpiSelectDevice( _SpiDevice Device )
{
                                       //Disable all SPI chip selects
   DrvFlashDisable();
   DrvSpiExtCsDisabled();

   switch( Device )
   {
      case SPI_DEVICE_NONE:
         break;

      case SPI_DEVICE_FLASH:			
         //DrvFlashEnable();
         break;

      case SPI_DEVICE_EXT_ADC:		
         break;
         
      case SPI_DEVICE_EEPROM:			   //
         break;

      case SPI_DEVICE_RTC:				   //
         break;

      case SPI_DEVICE_MMC:
         break;

      case SPI_DEVICE_ADC:
         break;

      case SPI_DEVICE_DAC:
         break; 
                  
      case SPI_DEVICE_TEMP:
         break; 
                                  
                                  
      case SPI_DEVICE_EXTERNAL:
         DrvSpiExtCsEnabled();
         break; 

      default:
         ;
   }
}

