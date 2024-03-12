#include "Timers.h"
#include "Servo.h"


void Servo_Init(void)   /**/
{
	ICR1_PR=19999;
	Servo_Pin=999;
}

void Servo_SetAngle (u8 Angle)
{
	u8 x=0;
	Servo_Pin=(((u32)x*1000)/180)+999;
	//Servo_Pin=((u32)(x/4)*1000/255)+999;    /* For using ADC to get the angle */
}
