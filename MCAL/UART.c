
#include "UART.h"


static void(*rxc_isr)(void) = (void *) 0x00 ;
static void(*txc_isr)(void) = (void *) 0x00 ;

void UART_Init(void)
{
	//boud rate 9600
	UBRRL_PR = 51 ;
	// enable transmitter and receiver
	SET_BIT(UCSRB_PR,RXEN) ;
	SET_BIT(UCSRB_PR,TXEN) ;
}
void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA_PR , UDRE)) ;
	UDR_PR = data ;
}
u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA_PR , RXC)) ;
	return UDR_PR ;
}

void UART_Send_Usinginterrupt(u8 data)
{
	UDR_PR = data ;
}
u8 UART_Receive_Usinginterrupt(void)
{
	return UDR_PR ;
}

void UART_Send_NoBlock(u8 data)
{
	UDR_PR = data ;
}
u8 UART_Receive_NoBlock(u8 *data)
{
	if(READ_BIT(UCSRA_PR,RXC))
	{
		*data = UDR_PR ;
		return 1 ;
	}
	else
	{
		return 0 ;
	}
}

void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB_PR,RXCIE) ;
}

void UART_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB_PR,RXCIE) ;
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB_PR,TXCIE) ;
}

void UART_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSRB_PR,TXCIE) ;
}

void UART_RXI_SetCallBack(void(*ptr)(void))
{
	rxc_isr = ptr ;
}

void UART_TXI_SetCallBack(void(*ptr)(void))
{
	txc_isr = ptr ;
}


ISR(UART_RX_vect)
{
	rxc_isr() ;
}

ISR(UART_TX_vect)
{
	txc_isr() ;
}
/*
	c++;
		if (c==16)
		{
			LCD_GoTo(2,0);
			//LCD_WriteCommand(0x06);
		}
		if (c==34)
		{
			LCD_Clear();
			LCD_GoTo(1,0);
			c=0;
		}
		x=UART_Receive();
		if (x!='z')
		{
			LCD_WriteChar(x);
		}
		if (x=='z')
		{
			u8 arr[7]={0b00001010,0b00010101,0b00010001,0b00001010,0b00000100,0b00000000,0b00000000};
			u8*ptr_char=&arr;
			LCD_Create_Character(arr,2);
			LCD_Init();
			LCD_WriteChar(2);
		}
*/

/*

u8 ledon[]="ledon" ;
u8 ledoff[]="ledoff" ;
u8 servo[]="servo" ;
u8 lcd[]="lcd" ;


u16 n1=0;
u16 n2=0;
u8 str[50]={0};
u8 stptr[10]={0};
u8 ndptr[10]={0};
	
UART_ReceiveString(str);
i=UART_Separating(str,stptr,ndptr,&n1,&n2);
if (i==1)
{
	LCD_Clear();
	LCD_GoTo(1,0);
	LCD_WriteString(stptr);
	LCD_GoTo(1,10);
	LCD_WriteNumber(n1);
	LCD_GoTo(2,0);
	LCD_WriteString(ndptr);
	LCD_GoTo(2,10);
	LCD_WriteNumber(n2);
	if (UART_CompareString(stptr,ledon))
	{
		DIO_WritePin((PIND_2+n1-1),HIGH);
	}
	else if (UART_CompareString(stptr,ledoff))
	{
		DIO_WritePin((PIND_2+n1-1),LOW);
	}
	else
	{
		LCD_Clear();
		LCD_GoTo(1,0);
		LCD_WriteString("Compare Error");
	}
}
else
{
	LCD_Clear();
	LCD_GoTo(1,0);
	LCD_WriteString("Frame Error");
}
*/