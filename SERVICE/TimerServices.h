


#ifndef TIMERSERVICES_H_
#define TIMERSERVICES_H_

#include "Timers.h"

void Timer0_SetInterrupt_us(u8 time , void(*pf)(void)) ;
void Timer0_SetInterrupt_ms(u16 time , void(*pf)(void)) ; 



void PWM_Measure(u32 *Pfreq , u8*Pduty) ; 



#endif /* TIMERSERVICES_H_ */