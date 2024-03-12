

// send : 
#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#include "UART.h"
#define END_OF_AYS_FN_CHARS			0x0D 

/*************Enter button in terminal is 0x0d*************/

void UART_SendString(u8 *str) ; 

void UART_ReceiveString(u8 *strptr) ; 

void  UART_ReceiveString_WithLength(u8 *strptr , u16 length) ; 

/***************************************************************************/

u8 UART_Separating(u8 *ptr,u8 *stptr,u8 *ndptr,u16 *pn1,u16 *pn2);
u8 UART_CompareString(u8 *s1,u8 *s2);

/************** Functions associated with TTL ( Prolific and Bluetooth module) *************/

void UART_SendLong_TTL(u32 data) ;

u32 UART_ReceiveLong_TTL(void) ;

u8 UART_Receive_NoBlock_TTL(u8 * ch) ;

void UART_SendString_WithLength_CheckSum_TTL(u8 *str) ;


/*******************************************************************************************/

/************ Functions associated with communicating between two mcus - on a binary level**/

void UART_SendLong(u32 data) ;

u32 UART_ReceiveLong(void) ;

void UART_SendString_CS(u8 *str) ; 

u8 UART_ReceiveString_CS(u8 *str) ; 

void UART_SendString_Using_Interrupt(u8 *str) ; 

void UART_ReceiveString_Interrupt(u8* str) ; 

void UART_ReceiveString_NotifyEnding_Interrupts(u8 *str) ;

u8 UART_ReceiveString_NotifyEnding_GetFlag(void) ;
/*******************************************************************************************/

void UART_SendString_M(u8*str);
u8 UART_ReceiveString_M(u8*str);

#endif /* UART_SERVICES_H_ */