
#define  F_CPU 8000000UL
#include <util/delay.h>


#include "MEMOMAP.h"
#include "STDTYPES.h"
#include "UTILS.h"
#include "DIO_INTERFACE.h"
#include "Stepper.h"
#include "Servo.h"
#include "KeyPad.h"
#include "LCD.h"
#include "ADC.h"
#include "Sensor.h"
#include "EXInterrupt.h"
#include "Timers.h"
#include "TimerServices.h"
#include "UART.h"
#include "UART_Services.h"
#include "SPI.h"

typedef unsigned char x ;
static volatile u16 duty=0,Ton=0,Toff=0,t1=0,t2=0,t3=0,c=0,flag=0,c_set=0,time=0,dis=0;;



static int i=200;

unsigned char SEGNUMBERS[10] = {0x3f ,0x06 ,0x5B ,0x4F ,0x66 ,0x6D ,0x7D ,0X07 ,0X7F ,0X6F};

void func1(void)
{
	DIO_TogglePin(PINB_5);
	c_set +=10;
}
void func2(void)
{
	DIO_TogglePin(PINB_4);
	c_set -=10;
}

void SEGMENT_DISPLAY(unsigned char n)
{
	PORTA_PR=SEGNUMBERS[n%10];
	PORTB_PR=SEGNUMBERS[n/10];
}

void SEGMENT_DISPLAY_2(unsigned char n)
{
	SET_BIT(PORTD_PR,1);
	CLEAR_BIT(PORTD_PR,0);
	PORTC_PR=SEGNUMBERS[n/10];
	_delay_ms(1);
	SET_BIT(PORTD_PR,0);
	CLEAR_BIT(PORTD_PR,1);
	PORTC_PR=SEGNUMBERS[n%10];
	_delay_ms(1);
}
void ICU_Func(void);



int main(void)
{
	// send :
	sei() ;
	DIO_Init();
	LCD_Init();
	UART_Init();
	SPI_InitMaster();
	//SPI_InitSlave();
	//ADC_Init(VREF_AVCC,ADC_SCALER_8);
	//Timer0_Init(TIMER0_NORMAL_MODE,TIMER0_SCALER_8,OCO_TOGGLE);
	//Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8,OCRA_DISCONNECTED,OCRB_DISCONNECTED);
	
	u8 i=0,x=0,y=0;
	y='a';
	LCD_WriteString("Mastr");
	while (1) 
	{
		
		
		SPI_SendReceive(y);
		y++;
		_delay_ms(100);
		/*LCD_Go_To(1,0);
		LCD_WriteChar(x);*/
	}
}
