 

#include "SPI.h"
// configure your pins as digital outputs ( associated with slave select ) .
void(*ptr_spi)(void) = (void *) 0x00 ; 
static DIO_Pin_type slave_arr[SS_NUMBER] = {PINB_0,PINB_1,PINB_2,PINB_3} ; // indexing starts from zero .. if no of slaves exceed SS_NUMBER change it in SPI.h file
void SPI_InitMaster(void) 
{
	SET_BIT(SPCR_PR,MSTR)  ;
	// clock 
	// polarity 
	// phase 
	SET_BIT(SPCR_PR,SPE)  ;
	
}
void SPI_InitSlave(void) 
{
	CLEAR_BIT(SPCR_PR,MSTR)  ;	
	// phase 
	SET_BIT(SPCR_PR,SPE)  ; // enable spi module
	
}
u8 SPI_SendReceive(u8 data)
{
	SPDR_PR = data ; 
	while(!(READ_BIT(SPSR_PR,SPIF))) ; // stucks for 8 cycles of the SPI cycles 
	return SPDR_PR ; 
	
}
u8 SPI_ReceiveNoBlock(void)
{
	return  SPDR_PR ; 
}
void SPI_SendNoBlock(u8 data)
{
	SPDR_PR = data ; 
}
u8 SPI_ReceivePeriodicChecking(u8 *data)
{
	if((CHECK_IF_BIT_SET_MODIFIED(SPSR_PR,SPIF)))
	{
		*data = SPDR_PR ; 
		return 1 ; 
	}
	return 0 ; // no data was received.

}
void SPI_InterruptEnable(void) 
{
	SET_BIT(SPCR_PR,SPIE) ; 
}
void SPI_InterruptDisable(void) 
{
	CLEAR_BIT(SPCR_PR,SPIE) ; 
}
void SPI_SendReceive_SetCallBack(void(*ptr)(void)) 
{
	ptr_spi = ptr ; 	
}

u8 SPI_SendReceive_SlaveSelect(u8 data , DIO_Pin_type ss_pin) 
{
	u8 i = 0  , received_data = 0 ; 
	/***************** Selecting the Slave by grounding the desired SS pin of the slaves ************/
	for(i = 0 ; i < SS_NUMBER ; i++)
	{
		if(i == ss_pin)
		{
			DIO_WritePin(slave_arr[i], LOW) ;
			continue ; 
		}
		DIO_WritePin(slave_arr[i], HIGH) ;
	}
	received_data = SPI_SendReceive(data) ; 
	return received_data ; 
}
ISR(SPI_STC_vect)
{
	ptr_spi() ; 
}