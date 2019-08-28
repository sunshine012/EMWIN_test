
/**
 * @file   DrvIOPort_MK70.c
 * @author Rick Johnson
 * @date   06/16/2014
 * @brief  Driver for the MK70 I/O ports.
 *
 * Contains all required definitions of IO ports for the MK70 Kinetis Arm
 */

////////////////////////////////////////////////////////////////////////////////
//
// Required include files.
//
////////////////////////////////////////////////////////////////////////////////

#include <DrvIOPort.h>

////////////////////////////////////////////////////////////////////////////////
//
// Local variables.
//
////////////////////////////////////////////////////////////////////////////////

#if (DRV_LIB_REV == 1000)
const CHAR DrvIOPortVersion[] = "1.0.0.0";
#else
const CHAR DrvIOPortVersion[] = "2.0.0.0";
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
 * @name    DrvIOPortGetVersion
 * @brief   Reports the I/O port driver verison
 * @ingroup Drivers
 *
 * This function returns I/O port driver version
 *
 * @param None 
 *
 * @retval const CHAR* -> version string
 *
 * Example Usage:
 * @code
 *    string = DrvIOPortGetVersion();
 * @endcode
 */

const CHAR* DrvIOPortGetVersion(void)
{
   return(DrvIOPortVersion);
}

/**
 * @name    DrvIOGetPortDirectionReg
 * @brief   Returns the port direction register
 * @ingroup Drivers
 *
 * This function gets the port direction register
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 *
 * @retval UINT32 Port Direction register
 *
 * Example Usage:
 * @code
 *    DdrReg = DrvIOGetPortDirectionReg(PTE_BASE_PTR); 
 * @endcode
 */

UINT32 DrvIOGetPortDirectionReg(GPIO_MemMapPtr pPortBaseAddr)
{
   return(pPortBaseAddr->PDDR);
}

/**
 * @name    DrvIOSetPortDirectionReg
 * @brief   Sets the port direction register
 * @ingroup Drivers
 *
 * This function sets the port direction register
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 * @param UINT32 DdrData
 *
 * @retval UINT8 IO_PORT_DIR_REG_SET
 *
 * Example Usage:
 * @code
 *    DdrReg = DrvIOSetPortDirectionReg(PTE_BASE_PTR, 0xFF00FF00); 
 * @endcode
 */

UINT8 DrvIOSetPortDirectionReg(GPIO_MemMapPtr pPortBaseAddr, UINT32 Data)
{
   pPortBaseAddr->PDDR = Data;         //direction register data
   return(IO_PORT_DIR_REG_SET);
}

/**
 * @name    DrvIOSetPortPinDirection
 * @brief   Sets the port pin direction
 * @ingroup Drivers
 *
 * This function sets the port pin direction. Port bit number 0-31
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 * @param BOOL Direction
 *
 * @retval UINT8 IO_PORT_DIR_REG_SET
 *
 * Example Usage:
 * @code
 *    status = DrvIOSetPortPinDirection(PTE_BASE_PTR, 0x00010000, IO_PORT_DDR_OUTPUT); 
 * @endcode
 */

UINT8 __optimize_level0__ DrvIOSetPortPinDirection(GPIO_MemMapPtr pPortBaseAddr, UINT32 Bit, BOOL Direction)
{
   UINT32 Data = 0x01;

   if(Bit > 31)
      return(IO_PORT_BIT_RANGE_ERROR);

   Data <<= Bit;

   if(Direction == IO_PORT_DDR_OUTPUT)
   {                                   //set bit
      pPortBaseAddr->PDDR |= (UINT32)Data;                
   }
   else
   {                                   //clear bit
      pPortBaseAddr->PDDR &= ((UINT32)Data ^ 0xFFFFFFFF);       
   }
   return(IO_PORT_BIT_DIR_SET);
}

/**
 * @name    DrvIOGetPortParFunction
 * @brief   Gets the port pin special function mode
 * @ingroup Drivers            
 *
 * This function gets the port pin special function mode. Port bit number 0-31
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 *
 * @retval UINT32 port special function register
 *
 * Example Usage:
 * @code
 *    Register = DrvIOGetPortParFunction(PTE_BASE_PTR, 0x00010000); 
 * @endcode
 */

UINT32 DrvIOGetPortParFunction(PORT_MemMapPtr pPortSfr, UINT32 Bit)
{
   return(pPortSfr->PCR[Bit]);
}

/**
 * @name    DrvIOSetPortParFunction
 * @brief   Sets the port pin special function mode
 * @ingroup Drivers            
 *
 * This function sets the port pin special function mode. Port bit number 0-31
 *
 * @param PORT_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 * @param UINT8 Function
 *
 * @retval UINT8 IO_PORT_BIT_DIR_SET
 *
 * Example Usage:
 * @code
 *    status = DrvIOSetPortParFunction(PTE_BASE_PTR , 0x00010000, IO_PORT_PIN_IO_FUNCTION6); 
 * @endcode
 */

UINT8 DrvIOSetPortParFunction(PORT_MemMapPtr pPortSfr, UINT32 Bit, UINT8 Function)
{
   if(Bit > 31)
      return(IO_PORT_BIT_RANGE_ERROR);
                                       //clear function and drive strength
   pPortSfr->PCR[Bit] &= ~(PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK | PORT_PCR_IRQC_MASK |
                           PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | 
                           PORT_PCR_PFE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_LK_MASK | 
                           PORT_PCR_ISF_MASK);

                                       //set new pin function and high drive strength
   pPortSfr->PCR[Bit] = PORT_PCR_MUX((UINT32)Function) | PORT_PCR_DSE_MASK;
   return(IO_PORT_BIT_DIR_SET);
}

/**
 * @name    DrvIOSetPortParFunctionEx
 * @brief   Sets the port pin special function mode with extended parameters
 * @ingroup Drivers            
 *
 * This function sets the port pin special function mode with extended parameters. Port bit number 0-31
 *
 * @param PORT_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 * @param _PORT_PCRMapPtr Configuration
 * @param UINT8 DigitalFilterEnabled
 * @param UINT8 DigitalFilterClock
 * @param UINT8 DigitalFilterWidth
 *
 * @retval UINT8 status
 *
 * Example Usage:
 * @code
 *    status = DrvIOSetPortParFunctionEx(PTE_BASE_PTR, 0x00010000, IO_PORT_PIN_IO_FUNCTION6, FALSE, 0, 4); 
 * @endcode
 */
                                
UINT8 DrvIOSetPortParFunctionEx(PORT_MemMapPtr pPortSfr, UINT32 Bit, _PORT_PCRMapPtr pConfiguration, 
                                UINT8 DigitalFilterEnabled, UINT8 DigitalFilterClock, UINT8 DigitalFilterWidth)
{
   UINT32 Data = 0x00000001;
   UINT32 oldDFER;
   
   if(Bit > 31)
      return(IO_PORT_BIT_RANGE_ERROR);
                                       //clear PCR registor for pin
   pPortSfr->PCR[Bit] &= ~(PORT_PCR_ISF_MASK | PORT_PCR_IRQC_MASK | PORT_PCR_LK_MASK | 
                           PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK | PORT_PCR_ODE_MASK | 
                           PORT_PCR_PFE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_PE_MASK |
                           PORT_PCR_PS_MASK);
                                       //set new pin function
   pPortSfr->PCR[Bit] = pConfiguration->PCRMapReg;
   
#if !defined(CONFIG_KINETIS_TYPE_MK22)
   oldDFER = pPortSfr->DFER;           //save current digital filter settings
   pPortSfr->DFER = 0x00000000;        //disable all digital filters
                                       //set filter width
   pPortSfr->DFWR = PORT_DFWR_FILT((UINT32)DigitalFilterWidth);
                                       
   Data <<= Bit;                       //move to bit location
   pPortSfr->DFCR &= ~Data;            //clear pin clock bit
   if(DigitalFilterClock)
      pPortSfr->DFCR |= Data;
   oldDFER &= ~Data;                   //clear pin digital filter enable
   if(DigitalFilterEnabled)            
   {
      oldDFER |= Data;                 //enable digital filter
   }
   pPortSfr->DFER = oldDFER;           //restore the digital filters
#endif
   return(IO_PORT_BIT_DIR_SET);
}

/**
 * @name    DrvIOSetPortBitData
 * @brief   Sets the port pin state
 * @ingroup Drivers            
 *
 * This function sets the port pin state. Port bit number 0-31
 *
 * @param PORT_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 * @param BOOL BitState
 *
 * @retval UINT8 status
 *
 * Example Usage:
 * @code
 *    status = DrvIOSetPortBitData(PTE_BASE_PTR, 0x00010000, 0); 
 * @endcode
 */

UINT8 DrvIOSetPortBitData(GPIO_MemMapPtr pPortBaseAddr, UINT32 Bit, BOOL BitState)
{
   UINT32 Data = 0x01;

   if(Bit > 31)
      return(IO_PORT_BIT_RANGE_ERROR);

   Data <<= Bit;

   if(BitState)
   {
      pPortBaseAddr->PSOR = Data;      //set output bit
   }
   else
   {                                   
      pPortBaseAddr->PCOR = Data;      //clear output bit  
   }
   return(IO_PORT_DATA_BIT_SET);
}

/**
 * @name    DrvIOSetPortRegData
 * @brief   Sets the port pins states
 * @ingroup Drivers            
 *
 * This function sets the port pins states. 
 *
 * @param PORT_MemMapPtr pPortBaseAddress
 * @param UINT32 Data
 *
 * @retval UINT8 status
 *
 * Example Usage:
 * @code
 *    status = DrvIOSetPortRegData(PTE_BASE_PTR, 0x00010000); 
 * @endcode
 */

UINT8 DrvIOSetPortRegData(GPIO_MemMapPtr pPortBaseAddr, UINT32 Data)
{
   pPortBaseAddr->PDOR = Data;          //output data
   return(IO_PORT_DATA_REG_SET);
}

/**
 * @name    DrvIOSetPortParIrqc
 * @brief   Sets port IRQE when configured as GPIO
 * @ingroup Drivers            
 *
 * This function sets port IRQE when configured as GPIO
 *
 * @param PORT_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 * @param _INTConfig Config
 *
 * @retval UINT8 status
 *
 * Example Usage:
 * @code
 *    status = DrvIOSetPortParIrqc(PTE_BASE_PTR , 0x00010000); 
 * @endcode
 */

UINT8 DrvIOSetPortParIrqc(PORT_MemMapPtr pPortSfr, UINT32 Bit, _INTConfig Config)
{
    if(Bit > 31)
       return(IO_PORT_BIT_RANGE_ERROR);

    pPortSfr->PCR[Bit] |= PORT_PCR_IRQC((UINT32)Config);
    
    return(IO_PORT_DATA_BIT_SET);    
}

/**
 * @name    DrvIOGetPortBitData
 * @brief   Gets port bit state
 * @ingroup Drivers            
 *
 * This function gets the port bit state
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 *
 * @retval UINT32 Bit data
 *
 * Example Usage:
 * @code
 *    Data = DrvIOGetPortBitData(PTE_BASE_PTR, 0x00010000); 
 * @endcode
 */

UINT32 __optimize_level0__ DrvIOGetPortBitData(GPIO_MemMapPtr pPortBaseAddr, UINT32 Bit)
{
   UINT32 Data = 0x01;

   if(Bit > 31)
      return(IO_PORT_BIT_RANGE_ERROR);

   Data <<= Bit;
   if(pPortBaseAddr->PDDR & Data)
   {                                   //port pin configured as output read data latch
                                       //register
      return((UINT32)((pPortBaseAddr->PDOR & Data) >> Bit));
   }
   else
   {                                   //port pin configured as input read 
                                       //pin data
      return((UINT32)((pPortBaseAddr->PDIR & Data) >> Bit));
   }
}

/**
 * @name    DrvIOGetPortRegData
 * @brief   Gets the port register data
 * @ingroup Drivers            
 *
 * This function gets port register data
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 *
 * @retval UINT32 port register data
 *
 * Example Usage:
 * @code
 *    Data = DrvIOGetPortRegData(PTE_BASE_PTR); 
 * @endcode
 */

UINT32 DrvIOGetPortRegData(GPIO_MemMapPtr PortBaseAddr)
{
   return(PortBaseAddr->PDIR);         //return port register data
}

/**
 * @name    DrvIOGetPortISFData
 * @brief   Clears port IRQE flag when when configured as GPIO
 * @ingroup Drivers            
 *
 * This function clears port IRQE flag when when configured as GPIO
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 *
 * @retval UINT32 port isfr register
 *
 * Example Usage:
 * @code
 *    Data = DrvIOGetPortISFData(PTE_BASE_PTR); 
 * @endcode
 */

UINT32 DrvIOGetPortISFData(PORT_MemMapPtr pPortSfr)
{
    UINT32 Data = pPortSfr->ISFR;    

    return (Data);
}

/**
 * @name    DrvIOGetPortParIrqc
 * @brief   Gets the port IRQ configuration when configured as GPIO
 * @ingroup Drivers            
 *
 * This function gets the port IRQ configuration when configured as GPIO
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 *
 * @retval _INTConfig 
 *
 * Example Usage:
 * @code
 *    Data = DrvIOGetPortParIrqc(PTE_BASE_PTR, 0x10000000); 
 * @endcode
 */

_INTConfig DrvIOGetPortParIrqc(PORT_MemMapPtr pPortSfr, UINT32 Bit)
{
    _INTConfig IntConfig = INT_DISABLED;
    UINT32 Reg = pPortSfr->PCR[Bit];
    
    Reg >>= PORT_PCR_IRQC_SHIFT;
    Reg &= 0xF;
    IntConfig = (_INTConfig)Reg;
    
    return(IntConfig);
}

/**
 * @name    DrvIOClearPortParIrqc
 * @brief   Clears port IRQE flag when when configured as GPIO
 * @ingroup Drivers            
 *
 * This function clears port IRQE flag when when configured as GPIO
 *
 * @param GPIO_MemMapPtr pPortBaseAddress
 * @param UINT32 Bit
 *
 * @retval UINT8 status
 *
 * Example Usage:
 * @code
 *    status = DrvIOClearPortParIrqc(PTE_BASE_PTR, 0x10000000); 
 * @endcode
 */

UINT8 DrvIOClearPortParIrqc(PORT_MemMapPtr pPortSfr, UINT32 Bit)
{
    if(Bit > 31)
       return(IO_PORT_BIT_RANGE_ERROR);

    pPortSfr->PCR[Bit] |= (((UINT32)(((UINT32)(1)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK);
    
    return(IO_PORT_DATA_BIT_SET);      
}

/**
 * @name    DrvIOGetPortBaseAddress
 * @brief   Returns base address of requested port
 * @ingroup Drivers            
 *
 * This function returns pointer to the base address of the passed port.  
 * Passed port is a capital letter
 *
 * @param CHAR -> letter of port
 * * A -> port A
 * * B -> port B
 * * C -> port C
 * * D -> port D
 * * E -> port E
 * * F -> port F
 *
 * @retval GPIO_MemMapPtr -> base address for port.  NULL indicates invalid port
 *
 * Example Usage:
 * @code
 *    pPort = DrvIOGetPortBaseAddress('A'); 
 * @endcode
 */

GPIO_MemMapPtr DrvIOGetPortBaseAddress(CHAR Port)
{
   GPIO_MemMapPtr pPortBaseAddress;

   switch(Port)                        
   {
      case 'A':
         pPortBaseAddress = PTA_BASE_PTR;
         break;

      case 'B':
         pPortBaseAddress = PTB_BASE_PTR;
         break;

      case 'C':
         pPortBaseAddress = PTC_BASE_PTR;
         break;

      case 'D':
         pPortBaseAddress = PTD_BASE_PTR;
         break;

      case 'E':
         pPortBaseAddress = PTE_BASE_PTR;
         break;

#if !defined(CONFIG_KINETIS_TYPE_MK22)
      case 'F':
         pPortBaseAddress = PTF_BASE_PTR;
         break;
#endif
      default:
         pPortBaseAddress = NULL;
   }
   return(pPortBaseAddress);
}

/**
 * @name    DrvIOGetPortSfrAddress
 * @brief   Returns SFR address of requested port
 * @ingroup Drivers            
 *
 * This function returns pointer to the special function register address of the passed port.  
 * Passed port is a capital letter
 *
 * @param CHAR -> letter of port
 * * A -> port A
 * * B -> port B
 * * C -> port C
 * * D -> port D
 * * E -> port E
 * * F -> port F
 *
 * @retval GPIO_MemMapPtr -> base address for port.  NULL indicates invalid port
 *
 * Example Usage:
 * @code
 *    pPortSFR = DrvIOGetPortSfrAddress('A'); 
 * @endcode
 */

PORT_MemMapPtr DrvIOGetPortSfrAddress(CHAR Port)
{
   PORT_MemMapPtr pPortSfr;

   switch(Port)                        
   {
      case 'A':
         pPortSfr = PORTA_BASE_PTR; 
         break;

      case 'B':
         pPortSfr = PORTB_BASE_PTR; 
         break;

      case 'C':
         pPortSfr = PORTC_BASE_PTR; 
         break;

      case 'D':
         pPortSfr = PORTD_BASE_PTR; 
         break;

      case 'E':
         pPortSfr = PORTE_BASE_PTR; 
         break;

#if !defined(CONFIG_KINETIS_TYPE_MK22)
      case 'F':
         pPortSfr = PORTF_BASE_PTR; 
         break;
#endif
      default:
         pPortSfr = NULL; 
   }
   return(pPortSfr);
}
