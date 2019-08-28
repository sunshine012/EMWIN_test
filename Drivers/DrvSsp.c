
#include <DrvIOPort.h>
#include <DrvSsp.h>

#ifndef CONFIG_MAX_SPP_PORTS
#define CONFIG_MAX_SPP_PORTS 7
#endif
UINT32   SspBaudRate[CONFIG_MAX_SPP_PORTS];

/**
 * @name    Ssp0Init
 * @brief   Initialize SSP channel 0
 * @ingroup Drivers
 *
 * Local function initializes the SSP channel 0
 *
 * @param UINT32 Baudrate -> in Hertz
 * @param UINT8 ClockInactiveLevel -> SPI_CLOCK_INACTIVE_LOW or SPI_CLOCK_INACTIVE_HIGH
 * @param UINT8 ClockPhase -> SPI_CLOCK_RISING_EDGE or SPI_CLOCK_FALLING_EDGE
 *
 * @retval UINT32 ActualBaudRate
 *
 * Example Usage:
 * @code
 *    ActualBaudRate = Ssp0Init(1000000, SPI_CLOCK_INACTIVE_LOW, SPI_CLOCK_RISING_EDGE);
 * @endcode
 */
UINT32 Ssp0Init(UINT32 BaudRate, UINT8 ClockInactiveLevel, UINT8 ClockPhase)
{
	UINT32   Div, SavedDiv, BinaryDiv, SavedBinaryDiv;
	UINT32   Pre, SavedPre, BinaryPre, SavedBinaryPre;
	UINT32   Baud, SavedBaud;

	Pre = 2;
	SavedBaud = 0;
	SavedPre = 0;
	BinaryPre = 0;
	SavedDiv = 0;
	SavedBinaryPre = 0;
	SavedBinaryDiv = 0;
	while (Pre <= 7) {
		BinaryDiv = 0;
		for (Div = 2; Div < 32768; Div *= 2) {
			Baud = SSP_CLOCK / (Pre * Div);

			if (Baud == BaudRate) { /* Exact baud match to desired baud. */
				SavedDiv = Div;
				SavedPre = Pre;
				SavedBinaryPre = BinaryPre;
				SavedBinaryDiv = BinaryDiv;
				break;
			} else if (Baud > SavedBaud && Baud < BaudRate) { /* From baud less than desired baud and greater than privously saved baud. */
				SavedBaud = Baud;
				SavedDiv = Div;
				SavedPre = Pre;
				SavedBinaryPre = BinaryPre;
				SavedBinaryDiv = BinaryDiv;
				break;
			} else {
			}
			BinaryDiv++;
		}
		if (Baud != BaudRate) { /* Try next pre value. */
			if (2 == Pre)
				Pre = 3;
			else if (3 == Pre)
				Pre = 5;
			else if (5 == Pre)
				Pre = 7;
			else
				break; /* Closest match without exceeding desired baud. */
			BinaryPre++;
		}
		else /* Exact match, done. */
			break;
	}

	SIM_SCGC6 |= (UINT32)0x1000;        //SPI module clock on
	//Stop the SPI0 module and reset
	SPI0_MCR = (UINT32)SPI_MCR_HALT_MASK;
	//set SPI mode
	SPI0_MCR |= (UINT32)(SPI_MCR_MSTR_MASK | SPI_MCR_FRZ_MASK | SPI_MCR_DOZE_MASK |
                        SPI_MCR_DIS_TXF_MASK | SPI_MCR_DIS_RXF_MASK | SPI_MCR_CLR_TXF_MASK |
                        SPI_MCR_CLR_RXF_MASK);
	SPI0_TCR = (UINT32)0x00;            //reset transfer counter

	SPI0_CTAR0 = (((SPI_TRANSFER_8BITS - 1) << SPI_CTAR_FMSZ_SHIFT) |
		((UINT32)ClockInactiveLevel << SPI_CTAR_CPOL_SHIFT) |
		((UINT32)ClockPhase << SPI_CTAR_CPHA_SHIFT) |
		(SavedBinaryPre << SPI_CTAR_PBR_SHIFT) | SavedBinaryDiv);
	//no clock doubling, 8 bits, inactive clock low,
	//capture on leading edge, MSB first,

	//clear flags
	SPI0_SR = (UINT32)(SPI_SR_TCF_MASK | SPI_SR_TXRXS_MASK | SPI_SR_EOQF_MASK |
			SPI_SR_TFUF_MASK | SPI_SR_TFFF_MASK |
			SPI_SR_RFOF_MASK | SPI_SR_RFDF_MASK);

	SPI0_RSER = (UINT32)0x00000000;     //select interrupt flags
	//enable the SPI
	SPI0_MCR &= (UINT32)~SPI_MCR_HALT_MASK;

	DrvIOSetPortBitData (SPI_PORT, SPI_CLK_BIT, ClockInactiveLevel);
	DrvIOSetPortBitData (SPI_PORT, SPI_RX_BIT, 1);
	DrvIOSetPortBitData (SPI_PORT, SPI_TX_BIT, 0);

	DrvIOSetPortParFunction(SPI_PORT_SFR, SPI_CLK_BIT, IO_PORT_PIN_IO_FUNCTION2);
	DrvIOSetPortPinDirection(SPI_PORT, SPI_CLK_BIT, IO_PORT_DDR_OUTPUT);
	DrvIOSetPortParFunction(SPI_PORT_SFR, SPI_RX_BIT, IO_PORT_PIN_IO_FUNCTION2);
	DrvIOSetPortPinDirection(SPI_PORT, SPI_RX_BIT, IO_PORT_DDR_INPUT);
	DrvIOSetPortParFunction(SPI_PORT_SFR, SPI_TX_BIT, IO_PORT_PIN_IO_FUNCTION2);
	DrvIOSetPortPinDirection(SPI_PORT, SPI_TX_BIT, IO_PORT_DDR_OUTPUT);

	return(SSP_CLOCK / (SavedPre * SavedDiv));
}

/**
 * @name    DrvSspDataTransitionLowToHigh
 * @brief
 * @ingroup Drivers
 *
 * Function
 *
 * @param None
 *
 * @retval void
 *
 * Example Usage:
 * @code
 *    DrvSspDataTransitionLowToHigh();
 * @endcode
 */
void DrvSspDataTransitionLowToHigh(void)
{
	asm("nop");
	SspDataTransitionLowToHigh();
	asm("nop");
}

/**
 * @name    DrvSspDataTransitionHighToLow
 * @brief
 * @ingroup Drivers
 *
 * Function
 *
 * @param None
 *
 * @retval void
 *
 * Example Usage:
 * @code
 *    DrvSspDataTransitionHighToLow();
 * @endcode
 */
void DrvSspDataTransitionHighToLow(void)
{
	asm("nop");
	SspDataTransitionHighToLow();
	asm("nop");
}

/**
 * @name    DrvSspInit
 * @brief   Initialize the SSP port
 * @ingroup Drivers
 *
 * Function initializes the SSP port baudrate
 *
 * @param int
 * * 0 -> serial flash
 * * 1 -> RFID
 * * 2 -> LCD
 * @param UINT32 BaudRate -> in Hertz
 *
 * @retval UINT32 ActualBaudRate -> in Hertz
 *
 * Example Usage:
 * @code
 *    ActualBaudRate = DrvSspInit(0, 1000000);   //port 0, baudrate 1MHz
 * @endcode
 */
UINT32 DrvSspInit(int Port, UINT32 BaudRate)
{
	switch (Port) {
	case 0:                  //Flash
		if (BaudRate > FLASH_MAX_BAUDRATE)
			BaudRate = FLASH_MAX_BAUDRATE;
		SspBaudRate[Port] = Ssp0Init(BaudRate, SPI_CLOCK_INACTIVE_LOW, SPI_CLOCK_RISING_EDGE);
		break;

	case 1:
		if (BaudRate > RFID_MAX_BAUDRATE)
			BaudRate = RFID_MAX_BAUDRATE;
		SspBaudRate[Port] = Ssp0Init(BaudRate, SPI_CLOCK_INACTIVE_LOW, SPI_CLOCK_RISING_EDGE);
		break;

#if defined(CONFIG_KINETIS_TYPE_MK20) || defined(CONFIG_KINETIS_TYPE_MK22)
	case 2:                  //External ADC
		if (BaudRate > EXT_ADC_MAX_BAUDRATE)
			BaudRate = EXT_ADC_MAX_BAUDRATE;
		SspBaudRate[Port] = Ssp0Init(BaudRate, SPI_CLOCK_INACTIVE_LOW, SPI_CLOCK_RISING_EDGE);
		break;
#elif defined(CONFIG_KINETIS_TYPE_MK70)
	case 2:                  //LCD
		if (BaudRate > LCD_MAX_BAUDRATE)
			BaudRate = LCD_MAX_BAUDRATE;
		SspBaudRate[Port] = Ssp0Init(BaudRate, SPI_CLOCK_INACTIVE_HIGH, SPI_CLOCK_FALLING_EDGE);
		break;
#else
#error "Invalid value for CONFIG_KINETIS_TYPE!"
#endif

	default:
		return 0;                    //ports 5 and 6 don't support synchronous mode
	}
	return(SspBaudRate[Port]);
}

/**
 * @name    DrvSspSpiWrite
 * @brief   Write 8 bit data to SSP
 * @ingroup Drivers
 *
 * Function clocks 8 bit data out to the SSP device
 *
 * @param int
 * * 0 -> serial flash
 * * 1 -> RFID
 * * 2 -> LCD
 * @param UINT8 Data
 *
 * @retval UINT8 Data
 *
 * Example Usage:
 * @code
 *    Data = DrvSspSpiWrite(0, 0x56);
 * @endcode
 */
UINT8 DrvSspSpiWrite(int Port, UINT8 Data)
{
	UINT32   SerialData = 0;

	switch (Port) {
	case 0:
#if defined(CONFIG_KINETIS_TYPE_MK70)
	case 1:
	case 2:
#endif
		//wait for space in queue
		while (!(SPI0_SR & SPI_SR_TFFF_MASK));

		//empty TX FIFO
		SPI0_MCR |= SPI_MCR_CLR_TXF_MASK;
		//add data to FIFO
		SPI0_PUSHR = ((UINT32)0 << SPI_PUSHR_CTAS_SHIFT) | SPI_PUSHR_EOQ_MASK |
			SPI_PUSHR_CTCNT_MASK | (0x0000FFFF & Data);
		//wait for write to finish
		while (!(SPI0_SR & SPI_SR_TCF_MASK));

		//read data from FIFO
		SerialData = SPI0_POPR;
		//clear transfer complete and end of queue flags
		SPI0_SR |=  SPI_SR_TCF_MASK | SPI_SR_EOQF_MASK;
		//clear RX FIFO
		SPI0_MCR |= SPI_MCR_CLR_RXF_MASK;
		break;

#if defined(CONFIG_KINETIS_TYPE_MK20) || defined(CONFIG_KINETIS_TYPE_MK22)
	case 1:
	case 2:
#endif
	case 4:
		break;

	default:
		;
	}

	return (UINT8)SerialData;
}

/**
 * @name    DrvSspSpiRead
 * @brief   Read 8 bit data from SSP
 * @ingroup Drivers
 *
 * Function clocks 8 bit data in from the SSP device.  Illegal port returns 0
 *
 * @param int
 * * 0 -> serial flash
 * * 1 -> RFID
 * * 2 -> LCD
 *
 * @retval UINT8 Data
 *
 * Example Usage:
 * @code
 *    Data = DrvSspSpiRead(0);
 * @endcode
 */
UINT8 DrvSspSpiRead(int Port)
{
	switch (Port) {
	case 0:
		return DrvSspSpiWrite(Port, 0xFF);

	case 1:
		return DrvSspSpiWrite(Port, 0xFF);

	case 2:
		return DrvSspSpiWrite(Port, 0xFF);

	case 3:
	case 4:
	case 5:
	case 6:
		break;
	}

	return 0;
}

/**
 * @name    DrvSspSpiWrite16
 * @brief   Write 16 bit data to SSP
 * @ingroup Drivers
 *
 * Function clocks 16 bit data out to the SSP device
 *
 * @param int
 * * 0 -> serial flash
 * * 1 -> RFID
 * * 2 -> LCD
 * @param UINT16 Data
 *
 * @retval void
 *
 * Example Usage:
 * @code
 *    DrvSspSpiWrite16(0, 0x1256);
 * @endcode
 */
UINT8 DrvSspSpiWrite16(int Port, UINT16 Data)
{
	UINT32 SerialData = 0;
	switch (Port) {
	case 0:
		DrvSspSpiWrite(0,(UINT8)((Data & 0xFF00)>>8));
		DrvSspSpiWrite(0,(UINT8)(Data & 0x00FF));
		break;

	case 1:
		DrvSspSpiWrite(1,(UINT8)((Data & 0xFF00)>>8));
		DrvSspSpiWrite(1,(UINT8)(Data & 0x00FF));
		break;

	case 2:
		DrvSspSpiWrite(2,(UINT8)((Data & 0xFF00)>>8));
		DrvSspSpiWrite(2,(UINT8)(Data & 0x00FF));
		break;

	case 3:
	case 4:
	case 5:
	case 6:
		break;

	default:
		;
	}

	return (UINT8)SerialData;
}

/**
 * @name    DrvSspGetBaudRate
 * @brief   Gets SSP baudrate
 * @ingroup Drivers
 *
 * Function gets the SSP current baudrate.
 *
 * @param int
 * * 0 -> serial flash
 * * 1 -> RFID
 * * 2 -> LCD
 *
 * @retval UINT32 BaudRate
 *
 * Example Usage:
 * @code
 *    Baudrate = DrvSspGetBaudRate(0);
 * @endcode
 */
UINT32 DrvSspGetBaudRate(int Port)
{
	switch (Port) {
	case 0:
	case 1:
	case 2:
		return SspBaudRate[Port];

	default:
		return 0;                    //ports 5 and 6 don't support synchronous mode
	}
}
