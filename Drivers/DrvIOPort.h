#ifndef DRV_IO_PORT_H
#define DRV_IO_PORT_H

#include "PE_Types.h"
#include "IO_Map.h"
#include "DrvTypeDefs.h"

//
// The following types define the internal structures of the different registers
// as specified in the datasheet.
//
typedef union PORT_PCRMap {
	UINT32 PCRMapReg;
	struct {
		UINT32 PinPullResistorSelect : 1;
		UINT32 PinPullResistorEnable : 1;
		UINT32 PinSlewRateEnable : 1;
		UINT32 Reserved0 : 1;
		UINT32 PinFilterEnable : 1;
		UINT32 PinOpenDrainEnable : 1;
		UINT32 PinDriveStrength : 1;
		UINT32 Reserved1 : 1;
		UINT32 PinSfrMode : 3;
		UINT32 Reserved2 : 4;
		UINT32 Lock : 1;
		UINT32 IntConfiguration : 4;
		UINT32 Reserved3 : 4;
		UINT32 IntStatus : 1;
		UINT32 Reserved4 : 7;
	} PCRMapBit;
} volatile *_PORT_PCRMapPtr;

//! Port pin interrupt modes
typedef enum {
	INT_DISABLED     = 0,
	INT_lOGIC_0      = 8,
	INT_RISING_EDGE  = 9,
	INT_FALLING_EDGE = 10,
	INT_EITHER_EDGE  = 11,
	INT_LOGIC_1      = 12
} _INTConfig, *_INTConfigPtr;

#define IO_PORT_DDR_OUTPUT          1  //!< Port pin DDR output mode
#define IO_PORT_DDR_INPUT           0  //!< Port pin DDR input mode

#define IO_PORT_BIT_DIR_SET         0  //!< Port pin bit set
#define IO_PORT_DIR_REG_SET         0  //!< Port pin DDR register direction set
#define IO_PORT_DATA_BIT_SET        0  //!< Port pin data bit set
#define IO_PORT_DATA_REG_SET        0  //!< Port pin data register set
#define IO_PORT_BIT_RANGE_ERROR     2  //!< Port pin range error
#define IO_PORT_PIN_IO_FUNCTION0    0  //!< Port pin special function 0
#define IO_PORT_PIN_IO_FUNCTION1    1  //!< Port pin special function 1
#define IO_PORT_PIN_IO_FUNCTION2    2  //!< Port pin special function 2
#define IO_PORT_PIN_IO_FUNCTION3    3  //!< Port pin special function 3
#define IO_PORT_PIN_IO_FUNCTION4    4  //!< Port pin special function 4
#define IO_PORT_PIN_IO_FUNCTION5    5  //!< Port pin special function 5
#define IO_PORT_PIN_IO_FUNCTION6    6  //!< Port pin special function 6
#define IO_PORT_PIN_IO_FUNCTION7    7  //!< Port pin special function 7

#define IO_PORT_PIN_IO_GPIO         IO_PORT_PIN_IO_FUNCTION1
#define IO_PORT_PIN_IO_ANALOG       IO_PORT_PIN_IO_FUNCTION0

typedef enum {
	IO_PORTA = 0,
	IO_PORTB,
	IO_PORTC,
	IO_PORTD,
	IO_PORTE,
	IO_PORTF,
} _IoPortIndex;

#define DrvIOTogglePinData(Port, Pin)  Port->PTOR = (0x00000001<< (UINT32)Pin)
#define DrvIOSetPinData(Port, Pin)	   Port->PSOR = (0x00000001<< (UINT32)Pin)
#define DrvIOClrPinData(Port, Pin)	   Port->PCOR = (0x00000001<< (UINT32)Pin)
#define DrvIOSetRegData(Port, Data)    Port->PDOR = Data

#define DrvIOGetPinData(Port, Pin)     ((Port->PDIR & (0x00000001<< (UINT32)Pin)) >> (UINT32)Pin)
#define DrvIOGetRegData(Port)          (Port->PDIR)

#define DrvIOSetRegDir(Port, Data)     Port->PDDR = Data
#define DrvIOSetPinOutput(Port, Pin)   Port->PDDR |= (0x00000001 << (UINT32)Pin)
#define DrvIOSetPinInput(Port, Pin)    Port->PDDR &= ((0x00000001 << (UINT32)Pin) ^ 0xFFFFFFFF)
#define DrvIOGetRegDir(Port)           (Port->PDDR)

UINT32 DrvIOGetPortDirectionReg(GPIO_MemMapPtr pPortBaseAddr);
UINT8 DrvIOSetPortDirectionReg(GPIO_MemMapPtr pPortBaseAddr, UINT32 Data);
UINT8 DrvIOSetPortPinDirection(GPIO_MemMapPtr pPortBaseAddr, UINT32 Bit, BOOL Direction);
UINT32 DrvIOGetPortParFunction(PORT_MemMapPtr pPortSfr, UINT32 Bit);
UINT8 DrvIOSetPortParFunction(PORT_MemMapPtr pPortSfr, UINT32 Bit, UINT8 Function);
UINT8 DrvIOSetPortParFunctionEx(PORT_MemMapPtr pPortSfr, UINT32 Bit, _PORT_PCRMapPtr pConfiguration, UINT8 DigitalFilterEnabled, UINT8 DigitalFilterClock, UINT8 DigitalFilterWidth);
UINT8 DrvIOSetPortBitData(GPIO_MemMapPtr pPortBaseAddr, UINT32 Bit, BOOL BitState);
UINT8 DrvIOSetPortRegData(GPIO_MemMapPtr pPortBaseAddr, UINT32 Data);
UINT8 DrvIOSetPortParIrqc(PORT_MemMapPtr pPortSfr, UINT32 Bit, _INTConfig Config);
UINT32 DrvIOGetPortBitData(GPIO_MemMapPtr pPortBaseAddr, UINT32 Bit);
UINT32 DrvIOGetPortRegData(GPIO_MemMapPtr pPortBaseAddr);
UINT32 DrvIOGetPortISFData(PORT_MemMapPtr pPortSfr);
_INTConfig DrvIOGetPortParIrqc(PORT_MemMapPtr pPortSfr, UINT32 Bit);
UINT8 DrvIOClearPortParIrqc(PORT_MemMapPtr pPortSfr, UINT32 Bit);
GPIO_MemMapPtr DrvIOGetPortBaseAddress(CHAR Port);
PORT_MemMapPtr DrvIOGetPortSfrAddress(CHAR Port);

#endif
