

#include "EXInterrupt.h"

static void (*FPtr_INT0)(void);
static void (*FPtr_INT1)(void);
static void (*FPtr_INT2)(void);

void EXI_Enable(EXInterruptSource_type interrupt)
{
	switch (interrupt)
	{
		case EX_INT0:
		SET_BIT(GICR_PR,EX_INT0);
		break;
		case EX_INT1:
		SET_BIT(GICR_PR,EX_INT1);
		break;
		case EX_INT2:
		SET_BIT(GICR_PR,EX_INT2);
		break;
	}
}


void EXI_Disable(EXInterruptSource_type interrupt)
{
	switch (interrupt)
	{
		case EX_INT0:
		CLEAR_BIT(GICR_PR,INT0);
		break;
		case EX_INT1:
		CLEAR_BIT(GICR_PR,INT1);
		break;
		case EX_INT2:
		CLEAR_BIT(GICR_PR,INT2);
		break;
	}
}


void EXI_TriggerEdge(EXInterruptSource_type interrupt,TriggerEdge_type edge)
{
	switch(interrupt)
	{
		case EX_INT0 :
		SET_BIT(GICR_PR,INT0);
		switch(edge)
		{
			case LOW_LEVEL :
			CLEAR_BIT(MCUCR_PR,ISC00);
			CLEAR_BIT(MCUCR_PR,ISC01);
			break ;
			case ANY_LOGIC_CHANGE :
			SET_BIT(MCUCR_PR,ISC00);
			CLEAR_BIT(MCUCR_PR,ISC01);
			break ;
			case FALLING_EDGE :
			CLEAR_BIT(MCUCR_PR,ISC00);
			SET_BIT(MCUCR_PR,ISC01);
			break ;
			case RISING_EDGE :
			SET_BIT(MCUCR_PR,ISC00);
			SET_BIT(MCUCR_PR,ISC01);
			break ;
		}
		break ;
		case EX_INT1 :
		SET_BIT(GICR_PR,INT1);
		switch(edge)
		{
			case LOW_LEVEL :
			CLEAR_BIT(MCUCR_PR,ISC10);
			CLEAR_BIT(MCUCR_PR,ISC11);
			break ;
			case ANY_LOGIC_CHANGE :
			SET_BIT(MCUCR_PR,ISC10);
			CLEAR_BIT(MCUCR_PR,ISC11);
			break ;
			case FALLING_EDGE :
			CLEAR_BIT(MCUCR_PR,ISC10);
			SET_BIT(MCUCR_PR,ISC11);
			break ;
			case RISING_EDGE :
			SET_BIT(MCUCR_PR,ISC10);
			SET_BIT(MCUCR_PR,ISC11);
			break ;
		}
		break ;
		case EX_INT2 :
		SET_BIT(GICR_PR,INT2);
		switch(edge)
		{
			case FALLING_EDGE :
			CLEAR_BIT(MCUCSR_PR,ISC2);
			break ;
			case RISING_EDGE :
			SET_BIT(MCUCSR_PR,ISC2);
			break ;
			default:
			CLEAR_BIT(MCUCSR_PR,ISC2);
			break ;
		}
		break ;
	}
}

void EXI_Set_Callback(EXInterruptSource_type interrupt,void(*pf_local)(void))
{
	switch (interrupt)
	{
		case EX_INT0:
		FPtr_INT0=pf_local;
		break;
		case EX_INT1:
		FPtr_INT1=pf_local;
		break;
		case EX_INT2:
		FPtr_INT2=pf_local;
		break;
	}
}

ISR(INT0_vect)
{
	if(FPtr_INT0!=NULLPTR)
	{
		FPtr_INT0();
	}
}

ISR(INT1_vect)
{
	if(FPtr_INT1!=NULLPTR)
	{
		FPtr_INT1();
	}
}

ISR(INT2_vect)
{
	if(FPtr_INT2!=NULLPTR)
	{
		FPtr_INT2();
	}
}