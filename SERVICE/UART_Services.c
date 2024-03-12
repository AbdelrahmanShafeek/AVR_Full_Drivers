
// FULL : 
#include "UART_Services.h"
#define DEBUG 0

static void uart_sendstring_isr(void) ;            // used in setcall back tx function 
static void uart_receivestring_isr(void) ;         // used in setcall back rx function
static void uart_receivestring_ended_isr(void) ;   // used in setcall back rx function
static u8 receive_complete_flag = 0 ;              // used with uart_receivestring_ended_isr
static u8 *pSendData = (void *) 0x00 ;
volatile static u8 *pRecData = (void *) 0x00 ;




void UART_SendString(u8 *str)
{
	u8 i=0;
	while (str[i]!=0x0d)
	{
		UART_Send(str[i]);
		i++ ;
	}
	UART_Send(0x0d);
	/*
	while(*x != '\0')
	{
		UART_Send(*x++) ;
	}
	UART_Send(END_OF_STRING_CHAR) ; 
	*/
}

void UART_ReceiveString(u8 *strptr)
{
	u8 x=0;
	strptr[x]=UART_Receive();
	while (strptr[x]!=0x0d)
	{
		x++;
		strptr[x]=UART_Receive();
	}
	strptr[x]=0;
	/*
	u16 i = 0 ;
	for(i = 0 ; (strptr[i] = UART_Receive() ) !=END_OF_STRING_CHAR ; i++) ;
	strptr[i] = '\0' ;
	*/
}

u8 UART_Separating(u8 *ptr,u8 *stptr,u8 *ndptr,u16 *pn1,u16 *pn2)
{
	u8 x=0,i=0,y=0,c1=0,c2=0;
	*pn1=0;
	*pn2=0;
	while (ptr[i]!=0)
	{
		i++;
		c1++;
	}
	i=0;
	while (ptr[i]!=',')
	{
		stptr[i]=ptr[i];
		i++;
		c2++;
	}
	stptr[i]=0;      /*3*/
	
	
	
	i++;             /*4*/
	for (x=0;ptr[i+x]!=',';x++)
	{
		if (ptr[i+x]>='0' && ptr[i+x]<='9')
		{
			*pn1=*pn1*10+ptr[i+x]-'0';
			c2++;
		}
		else
		{
			return 0;
		}
		
	}
	
	
	
	i=i+x+1;
	while (ptr[i]!=',')
	{
		ndptr[y]=ptr[i];
		i++;
		y++;
		c2++;
	}
	ndptr[y]=0;
	
	
	
	i++;                 /*6*/
	for (x=0;ptr[i+x];x++)
	{
		if (ptr[i+x]>='0' && ptr[i+x]<='9')
		{
			*pn2=*pn2*10+ptr[i+x]-'0';
			c2++;
		}
		else
		{
			return 0;
		}
	}
	
	
	
	c2=c2+3;
	if (c1==c2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

u8 UART_CompareString(u8 *s1,u8 *s2)
{
	for (u8 i=0;(s1[i]!=0)||(s2[i]!=0);i++)
	{
		if (s1[i]!=s2[i])
		{
			return 0;
		}
	}
	return 1;
}

void  UART_ReceiveString_WithLength(u8 *strptr , u16 length)
{
	u8 i = 0 ;
	for(i = 0 ; i < length ; i++)
	{
		strptr[i] = UART_Receive() ;
	}
	strptr[i] = '\0' ;
}
/************** Functions associated with TTL ( Prolific and Bluetooth module) *************/

void UART_SendLong_TTL(u32 data)
{
	u8 number_of_digits = 0  ,r = 0 ,i = 0 , x = 0  ;
	u32 rev = 0  ;
	while(data)
	{
		/********* Reversing the number ***********/
		r = data % 10 ;
		data /= 10 ;
		rev = rev * 10 + r ;
		/*****************************************/
		number_of_digits ++ ;
	}
	for(i = 0 ; i < number_of_digits ; i++)
	{
		x = rev % 10 ;
		UART_Send(x + '0') ;
		rev /= 10 ;
	}

	
}
u32 UART_ReceiveLong_TTL(void)
{
	u8 i = 0 ;
	u8 byte_rec = 0  ;
	u32 sum = 0  ;
	for(i = 0 ;(byte_rec = UART_Receive()) != END_OF_STRING_CHAR ; i++)
	{
		sum *= 10 ;
		sum += (byte_rec - '0') ;
	}

	
	return sum ;
}
u8 UART_Receive_NoBlock_TTL(u8 * ch)
{
	if(CHECK_IF_BIT_SET_MODIFIED(UCSRA_PR,RXC))
	{
		*ch = UDR_PR ;
		return 1 ; // receive completed
	}
	else
	{
		return 0 ;
	}
}
void UART_SendString_WithLength_CheckSum_TTL(u8 *str) 
{
	u8 i = 0 ; 
	u32 sum = 0 ; 
	while(str[i])
	{
		i++ ; 
	}
	UART_SendLong_TTL(i) ; 
	#if DEBUG 
	UART_SendString("\r\n") ; 
	#endif
	i = 0 ; 
	while(str[i])
	{
		UART_Send(str[i]) ; 
		sum += str[i] ; 
		i++ ;
	}
	UART_Send('\0') ; 
	#if DEBUG 
	UART_SendString("\r\n") ; 
	#endif
	UART_SendLong(sum) ; 
	#if DEBUG 
	UART_SendString("\r\n") ;
	UART_SendString("\r\n") ;
	#endif
	
	// mtnsash t3ml el recieve bta3ha
}

/*******************************************************************************************/

void UART_SendLong(u32 data) 
{
	UART_Send((u8) data) ;
	UART_Send((u8) (data >> 8)) ;
	UART_Send((u8) (data >> 16)) ;
	UART_Send((u8) (data >> 24)) ;

}

u32 UART_ReceiveLong(void) 
{
	u8 byte_1 = UART_Receive() ;
	u8 byte_2 = UART_Receive() ;
	u8 byte_3 = UART_Receive() ;
	u8 byte_4 = UART_Receive() ;
	u32 number = byte_1 | ((u32)byte_2<<8) | ((u32)byte_3<<16) | ((u32)byte_4 << 24) ; 
	return number ;  
}

void UART_SendString_CS(u8 *str)
{
	u8 i = 0 ; 
	u16 sum = 0 ; 
	for(i = 0 ; str[i] ; i++) 
	{
		sum += str[i] ; 
	}
	UART_Send(i) ; 
	for(i = 0 ; str[i] ; i++)
	{
		UART_Send(str[i]) ; 
	}
	UART_Send(sum) ; 
	UART_Send(sum >> 8) ; 
}

u8 UART_ReceiveString_CS(u8 *str)
{
	u8 length = 0  , byte_1 , byte_2 ; 
	u8 i = 0 ; 
	u16 sum_rec = 0  , sum = 0 ; 
	length = UART_Receive() ; 
	for(i = 0 ; i < length ; i++)
	{
		str[i] = UART_Receive() ; 
		//sum += str[i] ; 
	}
	//str[i] = '\0' ; 
	byte_1 = UART_Receive() ; 
	byte_2 = UART_Receive() ; 
	sum_rec = (u16) byte_1 | (u16) (byte_2 << 8) ; 
	if(sum == sum_rec)
	{
		return 1 ; 
	}
	else
	{
		return 0 ; 
	}
	
}

void UART_SendString_M(u8*str)
{
	u8 i=0;
	u16 sum=0;
	while (str[i])
	{
		i++;
	}
	UART_Send(i);
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
		sum+=str[i];
	}
	UART_Send(sum);
	UART_Send(sum>>8);
}

u8 UART_ReceiveString_M(u8*str)
{
	u8 length=0,i=0;
	u16 sum_rec=0,sum=0;
	length=UART_Receive();
	for (i=0;i<length;i++)
	{
		str[i]=UART_Receive();
		sum+=str[i];
	}
	sum_rec=UART_Receive();
	sum_rec=sum_rec<<8;
	sum_rec=UART_Receive();
	if (sum_rec==sum)
	{
		return 1;
	} 
	else
	{
		return 0;
	}
	
}

static void uart_sendstring_isr(void) // used in setcall back tx function
{
	static u8 i = 1;
	if(pSendData[i] != '\0')
	{
		UART_Send_NoBlock(pSendData[i]) ;
		i++ ;
	}
	else
	{
		i = 1 ; // to make the function be used the next time ;)
	}

}

void UART_SendString_Using_Interrupt(u8 *str)
{
	UART_TXI_SetCallBack(uart_sendstring_isr) ;
	UART_Send(str[0]) ;
	pSendData = str ;
}

static void uart_receivestring_isr(void)
{
	static u8 i = 0 ; 

		pRecData[i] = UDR_PR ; 
		i++ ; 

}

void UART_ReceiveString_Interrupt(u8* str)
{
	UART_RXI_SetCallBack(uart_receivestring_isr) ;
	pRecData = str ; 
}

static void uart_receivestring_ended_isr(void)
{
	static u8 i = 0 ;
	
	pRecData[i] = UDR_PR ;
	if(pRecData[i] != END_OF_AYS_FN_CHARS)
	{
		i++ ;
	}
	else
	{
		pRecData[i] = '\0' ; 
		receive_complete_flag = 1 ; 
		i = 0 ; 	
	}
}

void UART_ReceiveString_NotifyEnding_Interrupts(u8 *str)
{
	UART_RXI_SetCallBack(uart_receivestring_ended_isr) ;
	pRecData = str ;
}

u8 UART_ReceiveString_NotifyEnding_GetFlag(void) 
{
	if(receive_complete_flag == 1)
	{
		receive_complete_flag = 0 ; 
		return 1 ; 
	}
	else
	{
		return 0 ; 
	}
}
