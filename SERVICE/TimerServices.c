

 
#include "Timers.h"

/****************************** Functions Based on Timer 0 CTC mode variables and functions prototypes ********/

static void (*pf_OCR0)(void) = (void *) 0x00 ; 
static u8 counter = 0 ;
static u8 counter_set = 0 ;
void func_oc(void) ; // a function used in  Timer0_SetInterrupt_ms
/***************************************************************************************************************/
/****************************** Functions Based on Timer 1 Input Capture unit variables and functions prototypes */
/*****************************************************************************************************************/
static volatile u8 press_flag = 0 ; 
static volatile u16 t1 = 0, t2 = 0 , t3 = 0 ; 
static volatile u32 ovf_counter = 0 ; 
static void icu_func(void) ; 
static void ovf_func(void) ; 
/****************************** Functions Based on Timer 0 CTC mode ********************************************/

// time is passed in u Seconds , when the prescaler of the timer = 0 is 8 , you must enable interrupt for Output compare match and initialize Timer0 in CTC mode first
void Timer0_SetInterrupt_us(u8 time , void(*pf)(void) )
{
	OCR0_PR = time - 1 ; 
	TIMER0_OC_SetCallBack(pf) ; 
}
void func_oc(void)
{
	counter ++ ; 
	if(counter == counter_set)
	{
		pf_OCR0() ; 
		counter = 0 ; 	
	}
}
void Timer0_SetInterrupt_ms(u16 time , void(*pf)(void))
{
	OCR0_PR = 200 - 1 ;
	counter_set = (time * 1000) /  200 ; 
	pf_OCR0 = pf ; 
	TIMER0_OC_SetCallBack(func_oc) ;
}
// don't forget to use timer 1 ( implement these two functions using timer 1) 
/********************************************************************************************/






/* The function bellow  works when : 
1 - Timer 1 is in normal mode.
2 - Interrupts are enabled for ICP pin.
3 - Global interrupts are enabled.
4 - when you want to use the Overflow ISR of timer 1 , use it here .. Extremely important
*/
void PWM_Measure(u32 *Pfreq , u8*Pduty)
{
	u16 time_on = 0 , time_off = 0 , time_total = 0 ;
	Timer1_OVF_SetCallBack(ovf_func) ;
	Timer1_ICU_SetCallBack(icu_func) ;
	Timer1_ICU_InterruptEnable() ;
	Timer1_InputCaptureEdge(RISING) ;
	
	
	while(press_flag < 3) ; // the function won't return unles it gets the correct reading
	time_on = t2  + ovf_counter * 65536 - t1 ;
	time_off = t3 + ovf_counter * 65536 - t2  ;
	time_total = (u32) time_on + (u32)time_off ;
	*Pduty = ((u32)time_on * 100) / time_total ;
	*Pfreq = 1000000 / (u32) time_total ;
	ovf_counter = 0 ; 	
	Timer1_ICU_InterruptEnable() ; 
	press_flag = 0 ;
	
		
}
static void icu_func(void)
{
	if(press_flag == 0) // a rising edge occured.
	{
		t1 = ICR1_PR ;
		Timer1_InputCaptureEdge(FALLING) ;
		press_flag = 1 ;
	}
	else if(press_flag == 1) // a falling edge occured
	{
		t2 = ICR1_PR ;
		Timer1_InputCaptureEdge(RISING) ;
		press_flag = 2 ;
	}
	else if(press_flag == 2) // a rising edge occured
	{
		t3 = ICR1_PR ;
		// keep the edge as it is
		press_flag = 3 ;
		Timer1_ICU_InterruptDisable() ; // Disable useless interrupts when flag = 3 and I haven't read t1 , t2 , t3 yet
	}
}
static void ovf_func(void)
{
	ovf_counter ++ ;
}
