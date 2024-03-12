/*
 * DIO_INTERFACE.h
 *
 * Created: 8/25/2021 3:59:33 PM
 *  Author: Dell
 */ 


#ifndef DIO_INTERFERENCE_H_
#define DIO_INTERFERENCE_H_


#include "STDTYPES.h"
#include "MEMOMAP.h"
#include "UTILS.h"
typedef enum
{
	PINA_0=0,
	PINA_1,
	PINA_2,
	PINA_3,
	PINA_4,
	PINA_5,
	PINA_6,
	PINA_7,
	PINB_0,
	PINB_1,
	PINB_2,
	PINB_3,
	PINB_4,
	PINB_5,
	PINB_6,
	PINB_7,
	PINC_0,
	PINC_1,
	PINC_2,
	PINC_3,
	PINC_4,
	PINC_5,
	PINC_6,
	PINC_7,
	PIND_0,
	PIND_1,
	PIND_2,
	PIND_3,
	PIND_4,
	PIND_5,
	PIND_6,
	PIND_7,
	TOTAL_PINS
}DIO_Pin_type;

typedef enum
{
	OUTPUT,
	INFREE,
	INLLUP
}DIO_PinStatus_type;

typedef enum
{
	PA=0,
	PB,
	PC,
	PD
}DIO_Port_type;

typedef enum
{
	LOW=0,
	HIGH
	
}DIO_Voltage_type;



extern void DIO_InitPin(DIO_Pin_type pin,DIO_PinStatus_type status );
extern void DIO_WritePin(DIO_Pin_type pin,DIO_Voltage_type volt);
extern DIO_Voltage_type DIO_ReadPin(DIO_Pin_type pin);
extern void DIO_TogglePin(DIO_Pin_type pin);

extern void DIO_WritePort(DIO_Port_type port ,u8 value);
extern u8 DIO_ReadPort(DIO_Port_type port);
extern void DIO_Init(void);
extern const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS];


#endif /* DIO_INTERFACE_H_ */