

#include "Timers.h"

#define NULLPTR (void *) 0x00  

// Timer0 Functions : 
static void (*pf_TIMER0_OV)(void) = (void*) 0x00;
static void (*pf_TIMER0_OC)(void) = (void*) 0x00;

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*Timer1_OVF_Fptr) (void)=NULLPTR;
static void (*Timer1_OCA_Fptr) (void)=NULLPTR;
static void (*Timer1_OCB_Fptr) (void)=NULLPTR;
static void (*Timer1_ICU_Fptr) (void)=NULLPTR;
/**************************************************************************/

void Timer0_Init( Timer0_Mode_type mode,Timer0_Scaler_type scaler ,OC0_Mode_type oc_mode)
{
	/************************ Choosing a Prescaler *******************************/
	TCCR0_PR &= ~ 0x07 ; // Clearing CS00 , CS01 , and CS02.
	TCCR0_PR |= scaler ; // Getting the combination of CS00 , CS01 , and CS02 into the TCCR0 register without affecting other settings.
	/*****************************************************************************/
	
	
	/***************** Choosing Mode of TIMER0 ***********************************/
	switch(mode)
	{
		/************* Normal Mode ***********************************************/
		case TIMER0_NORMAL_MODE :
			switch(oc_mode)
			{
				case OCO_DISCONNECTED :
					CLEAR_BIT(TCCR0_PR,COM00) ;
					CLEAR_BIT(TCCR0_PR,COM01) ;
				break ; 
				
				case OCO_TOGGLE :
					SET_BIT(TCCR0_PR,COM00) ;
					CLEAR_BIT(TCCR0_PR,COM01) ;					
				break ;
				
				case OCO_NON_INVERTING :
					CLEAR_BIT(TCCR0_PR,COM00) ;
					SET_BIT(TCCR0_PR,COM01) ;
				break ; 
				
				case OCO_INVERTING :
					SET_BIT(TCCR0_PR,COM00) ;
					SET_BIT(TCCR0_PR,COM01) ;
				break ; 
				
			}
			CLEAR_BIT(TCCR0_PR ,WGM00) ;
			CLEAR_BIT(TCCR0_PR ,WGM01) ;	
		break ; 
		/**************************************************************************************/
		
		/************* Phase Correct PWM Mode  ***********************************************/
		case TIMER0_PHASECORRECT_MODE :
			switch(oc_mode)
			{
				case OCO_DISCONNECTED :
				CLEAR_BIT(TCCR0_PR,COM00) ;
				CLEAR_BIT(TCCR0_PR,COM01) ;
				break ;
				
				case OCO_NON_INVERTING :
				CLEAR_BIT(TCCR0_PR,COM00) ;
				SET_BIT(TCCR0_PR,COM01) ;
				break ;
				
				case OCO_INVERTING :
				SET_BIT(TCCR0_PR,COM00) ;
				SET_BIT(TCCR0_PR,COM01) ;
				break ;
				
				default: 
				break ; 
				
			}
			SET_BIT(TCCR0_PR ,WGM00) ;
			CLEAR_BIT(TCCR0_PR ,WGM01) ;
		break ; 
		/**************************************************************************************/
		
		/************* Clear Timer On Output Mode(CTC) ****************************************/
		case TIMER0_CTC_MODE :
			switch(oc_mode)
			{
				case OCO_DISCONNECTED :
				CLEAR_BIT(TCCR0_PR,COM00) ;
				CLEAR_BIT(TCCR0_PR,COM01) ;
				break ;
				
				case OCO_TOGGLE :
				SET_BIT(TCCR0_PR,COM00) ;
				CLEAR_BIT(TCCR0_PR,COM01) ;
				break ;
				
				case OCO_NON_INVERTING :
				CLEAR_BIT(TCCR0_PR,COM00) ;
				SET_BIT(TCCR0_PR,COM01) ;
				break ;
				
				case OCO_INVERTING :
				SET_BIT(TCCR0_PR,COM00) ;
				SET_BIT(TCCR0_PR,COM01) ;
				break ;
				
			}
			CLEAR_BIT(TCCR0_PR ,WGM00) ;
			SET_BIT(TCCR0_PR ,WGM01) ;
		break ; 
		/***************************************************************************/

		/************* Fast PWM Mode ***********************************************/
		case TIMER0_FASTPWM_MODE :
			switch(oc_mode)
			{
				case OCO_DISCONNECTED :
				CLEAR_BIT(TCCR0_PR,COM00) ;
				CLEAR_BIT(TCCR0_PR,COM01) ;
				break ;
				
				case OCO_NON_INVERTING :
				CLEAR_BIT(TCCR0_PR,COM00) ;
				SET_BIT(TCCR0_PR,COM01) ;
				break ;
				
				case OCO_INVERTING :
				SET_BIT(TCCR0_PR,COM00) ;
				SET_BIT(TCCR0_PR,COM01) ;
				break ;
				
				default: 
				break ; 
				
			}
			SET_BIT(TCCR0_PR ,WGM00) ;
			SET_BIT(TCCR0_PR ,WGM01) ;
		break ;  
		/******************************************************************************************/
	}
	

	
}
void Timer0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK_PR,TOIE0) ; 
}
void Timer0_OV_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK_PR,TOIE0) ;
}
void Timer0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK_PR,OCIE0) ; 
}
void Timer0_OC_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK_PR,OCIE0) ; 
}
void TIMER0_OV_SetCallBack(void (*localpf)(void)) 
{
	pf_TIMER0_OV = localpf ;
}
void TIMER0_OC_SetCallBack(void (*localpf)(void)) 
{
	pf_TIMER0_OC = localpf ;
}
ISR(TIMER0_OVF_vect)
{
	pf_TIMER0_OV() ; 
}
ISR(TIMER0_OC_vect)
{
	pf_TIMER0_OC() ; 
}
// Timer 1 
/****************************************Timer 1 **********************************************/

void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler,OC1A_Mode_type oc1a_mode,OC1B_Mode_type oc1b_mode)

{
	switch (mode)
	{
		case TIMER1_NORMAL_MODE:
		CLEAR_BIT(TCCR1A_PR,WGM10);
		CLEAR_BIT(TCCR1A_PR,WGM11);
		CLEAR_BIT(TCCR1B_PR,WGM12);
		CLEAR_BIT(TCCR1B_PR,WGM13);
		break;
		case TIMER1_CTC_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A_PR,WGM10);
		CLEAR_BIT(TCCR1A_PR,WGM11);
		SET_BIT(TCCR1B_PR,WGM12);
		SET_BIT(TCCR1B_PR,WGM13);
		break;
		
		case TIMER1_CTC_OCRA_TOP_MODE:
		CLEAR_BIT(TCCR1A_PR,WGM10);
		CLEAR_BIT(TCCR1A_PR,WGM11);
		SET_BIT(TCCR1B_PR,WGM12);
		CLEAR_BIT(TCCR1B_PR,WGM13);
		break;
		
		case TIMER1_FASTPWM_ICR_TOP_MODE:
		CLEAR_BIT(TCCR1A_PR,WGM10);
		SET_BIT(TCCR1A_PR,WGM11);
		SET_BIT(TCCR1B_PR,WGM12);
		SET_BIT(TCCR1B_PR,WGM13);
		break;
		
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		SET_BIT(TCCR1A_PR,WGM10);
		SET_BIT(TCCR1A_PR,WGM11);
		SET_BIT(TCCR1B_PR,WGM12);
		SET_BIT(TCCR1B_PR,WGM13);
		break;
	}
	switch (oc1a_mode)
	{
		case OCRA_DISCONNECTED:
		CLEAR_BIT(TCCR1A_PR,COM1A0);
		CLEAR_BIT(TCCR1A_PR,COM1A1);
		break;
		case OCRA_TOGGLE:
		SET_BIT(TCCR1A_PR,COM1A0);
		CLEAR_BIT(TCCR1A_PR,COM1A1);
		break;
		case OCRA_NON_INVERTING:
		CLEAR_BIT(TCCR1A_PR,COM1A0);
		SET_BIT(TCCR1A_PR,COM1A1);
		break;
		case OCRA_INVERTING:
		SET_BIT(TCCR1A_PR,COM1A0);
		SET_BIT(TCCR1A_PR,COM1A1);
		break;
	}
	switch (oc1b_mode)
	{
		case OCRB_DISCONNECTED:
		CLEAR_BIT(TCCR1A_PR,COM1B0);
		CLEAR_BIT(TCCR1A_PR,COM1B1);
		break;
		case OCRB_TOGGLE:
		SET_BIT(TCCR1A_PR,COM1B0);
		CLEAR_BIT(TCCR1A_PR,COM1B1);
		break;
		case OCRB_NON_INVERTING:
		CLEAR_BIT(TCCR1A_PR,COM1B0);
		SET_BIT(TCCR1A_PR,COM1B1);
		break;
		case OCRB_INVERTING:
		SET_BIT(TCCR1A_PR,COM1B0);
		SET_BIT(TCCR1A_PR,COM1B1);
		break;
	}
	
	
	TCCR1B_PR&=0XF8;
	TCCR1B_PR|=scaler;

}

void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if(edge==RISING)
	SET_BIT(TCCR1B_PR,ICES1);
	
	else if(edge==FALLING)
	CLEAR_BIT(TCCR1B_PR,ICES1);

}
/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK_PR,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK_PR,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK_PR,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK_PR,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK_PR,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK_PR,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK_PR,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK_PR,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr=LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr=LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr=LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULLPTR)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!=NULLPTR)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!=NULLPTR)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!=NULLPTR)
	{
		Timer1_ICU_Fptr();
	}
}