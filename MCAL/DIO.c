
 

#include "DIO_INTERFACE.h"
#include "STDTYPES.h"
#include "Utils.h"
#include "MEMOMAP.h"
void DIO_InitPin(DIO_Pin_type pin , DIO_PinStatus_type status )
{
	DIO_Port_type port =pin/8;
	u8 pin_num=pin%8;
	switch(status)
	{
		case INFREE:
		switch(port)
		{
			case PA:
			CLEAR_BIT(DDRA_PR,pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB_PR,pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRC_PR,pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD_PR,pin_num);
			break;
		}
		break;
		case INLLUP :
		switch(port)
		{
			case PA:
			CLEAR_BIT(DDRA_PR,pin_num);
			SET_BIT(PORTA_PR,pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB_PR,pin_num);
			SET_BIT(PORTB_PR,pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRC_PR,pin_num);
			SET_BIT(PORTC_PR,pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD_PR,pin_num);
			SET_BIT(PORTD_PR,pin_num);
			break;
		}
		break;
		case OUTPUT :
		switch(port)
		{
			case PA:
			SET_BIT(DDRA_PR,pin_num);
			break;
			case PB:
			SET_BIT(DDRB_PR,pin_num);
			break;
			case PC:
			SET_BIT(DDRC_PR,pin_num);
			break;
			case PD:
			SET_BIT(DDRD_PR,pin_num);
			break;
		}
		break;
	}
	
}


void DIO_WritePin(DIO_Pin_type pin ,DIO_Voltage_type volt)
{
	DIO_Port_type port =pin/8;
	u8 pin_num=pin%8;
	if (volt == HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA_PR,pin_num);
			break;
			case PB:
			SET_BIT(PORTB_PR,pin_num);
			break;
			case PC:
			SET_BIT(PORTC_PR,pin_num);
			break;
			case PD:
			SET_BIT(PORTD_PR,pin_num);
			break;
		}
	}
	else if(volt == LOW)
	{
		switch(port)
		{
			case PA:
			CLEAR_BIT(PORTA_PR,pin_num);
			break;
			case PB:
			CLEAR_BIT(PORTB_PR,pin_num);
			break;
			case PC:
			CLEAR_BIT(PORTC_PR,pin_num);
			break;
			case PD:
			CLEAR_BIT(PORTD_PR,pin_num);
			break;
		}
	}

}


DIO_Voltage_type DIO_ReadPin(DIO_Pin_type pin)
{
	DIO_Port_type port =pin/8;
	u8 pin_num=pin%8;
	DIO_Voltage_type volt ;
	switch(port)
	{
		case PA:
		volt=READ_BIT(PINA_PR,pin_num);
		break;
		case PB:
		volt=READ_BIT(PINB_PR,pin_num);
		break;
		case PC:
		volt=READ_BIT(PINC_PR,pin_num);
		break;
		case PD:
		volt=READ_BIT(PIND_PR,pin_num);
		break;
	}
	return volt;
}

void DIO_TogglePin(DIO_Pin_type pin)
{
	DIO_Port_type port =pin/8;
	u8 pin_num=pin%8;
	
	switch(port)
	{
		case PA:
		TOGGLE_BIT(PORTA_PR,pin_num);
		break;
		case PB:
		TOGGLE_BIT(PORTB_PR,pin_num);
		break;
		case PC:
		TOGGLE_BIT(PORTC_PR,pin_num);
		break;
		case PD:
		TOGGLE_BIT(PORTD_PR,pin_num);
		break;
	}
}


void DIO_WritePort(DIO_Port_type port , u8 data)
{
	switch(port)
	{
		case PA:
		PORTA_PR = data ;
		break;
		case PB:
		PORTB_PR = data ;
		break;
		case PC:
		PORTC_PR = data ;
		break;
		case PD:
		PORTD_PR = data ;
		break;
		
	}
}


u8 DIO_ReadPort(DIO_Port_type port)
{
	u8 data;
	switch(port)
	{
		case PA:
		data =PINA_PR ;
		break;
		case PB:
		data =PINB_PR ;
		break;
		case PC:
		data =PINC_PR ;
		break;
		case PD:
		data =PIND_PR ;
		break;
	}return data;

}

void DIO_Init(void)
{
	DIO_Pin_type i;
	for (i=PINA_0;i<32;i++)
	{
		DIO_InitPin(i,PinsStatusArray[i]);
	}
}
