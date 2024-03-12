

#ifndef SPI_H_
#define SPI_H_

#include "MEMOMAP.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"

#define		SS_NUMBER		4

void SPI_InitMaster(void) ; 
void SPI_InitSlave(void) ; 
u8 SPI_SendReceive(u8 data) ; 
void SPI_SendNoBlock(u8 data) ; 
u8 SPI_ReceiveNoBlock(void) ; 
u8 SPI_ReceivePeriodicChecking(u8 *data) ; 
void SPI_InterruptEnable(void) ;
void SPI_InterruptDisable(void) ;
void SPI_SendReceive_SetCallBack(void(*ptr)(void)) ;

// Master Mode only 
u8 SPI_SendReceive_SlaveSelect(u8 slave_index,u8 data) ; // slave index starts from 0 . 


#endif /* SPI_H_ */