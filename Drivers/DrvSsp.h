#ifndef DRV_SSP_H
#define DRV_SSP_H

#include "DrvTypeDefs.h"
#include "PE_Types.h"
#include "IO_Map.h"
#include "Cpu.h"

#define SSP_DISABLE                 0
#define SSP_ENABLE                  1

#define SSP_CLOCK_INTERNAL_SCK_IO   0x00
#define SSP_CLOCK_EXTERNAL_SCK_IO   0x01

#define SSP_CLOCK                   CPU_BUS_CLK_HZ

#define FLASH_MAX_BAUDRATE      75000000
#define RFID_MAX_BAUDRATE       2000000
#define EXT_ADC_MAX_BAUDRATE	20000000
#define LCD_MAX_BAUDRATE	20000000

#define SPI_TRANSFER_8BITS          8
#define SPI_CLOCK_INACTIVE_HIGH     1
#define SPI_CLOCK_INACTIVE_LOW      0
#define SPI_CLOCK_RISING_EDGE       0
#define SPI_CLOCK_FALLING_EDGE      1

#define SPI_PORT                    PTA_BASE_PTR
#define SPI_PORT_SFR                PORTA_BASE_PTR
#define SPI_RX_BIT                  17
#define SPI_TX_BIT                  16
#define SPI_CLK_BIT                 15

#define DrvSspEnabled()                SPI0_MCR &= ~SPI_MCR_HALT_MASK
#define DrvSspDisabled()               SPI0_MCR |= SPI_MCR_HALT_MASK
#define SspDataTransitionHighToLow()   SPI0_CTAR0 |= SPI_CTAR_CPHA_MASK
#define SspDataTransitionLowToHigh()   SPI0_CTAR0 &= ~SPI_CTAR_CPHA_MASK

UINT32 DrvSspInit(int Port, UINT32 BaudRate);
UINT8 DrvSspSpiWrite(int Port, UINT8 Data);
UINT8 DrvSspSpiRead(int Port);
UINT8 DrvSspSpiWrite16(int Port, UINT16 Data);
UINT32 DrvSspGetBaudRate(int Port);
void DrvSspDataTransitionLowToHigh(void);
void DrvSspDataTransitionHighToLow(void);

#endif
