
#ifndef TIMERS_H_
#define TIMERS_H_

#include "StdTypes.h"
#include "Utils.h"
#include "MEMOMAP.H"


typedef enum{
	// There is no need to put numbers , I'm doing do for clarification.
	TIMER0_STOP=0x00 ,
	TIMER0_SCALER_1 = 0x01 ,
	TIMER0_SCALER_8 = 0x02,
	TIMER0_SCALER_64 = 0x03 ,
	TIMER0_SCALER_256 = 0x04 ,
	TIMER0_SCALER_1024 = 0x05 ,
	EXTERNALl_FALLING = 0x06 ,
	EXTERNAL_RISING = 0x07 ,
}Timer0_Scaler_type;

typedef enum
{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE

}Timer0_Mode_type;
typedef enum
{
	OCO_DISCONNECTED=0,
	OCO_TOGGLE,
	OCO_NON_INVERTING,
	OCO_INVERTING

}OC0_Mode_type;



void Timer0_Init( Timer0_Mode_type mode,Timer0_Scaler_type scaler ,OC0_Mode_type oc_mode);
void Timer0_OV_InterruptEnable(void);
void Timer0_OV_InterruptDisable(void); // you must set the global interrupt flag before using this function
void Timer0_OC_InterruptEnable(void);
void Timer0_OC_InterruptDisable(void);
void TIMER0_OV_SetCallBack(void (*localpf)(void)) ; 
void TIMER0_OC_SetCallBack(void (*localpf)(void)) ; 
/*********************************************************************************************************/

typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}Timer1Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE

}Timer1Mode_type;

typedef enum
{
	OCRA_DISCONNECTED=0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING

}OC1A_Mode_type;

typedef enum
{
	OCRB_DISCONNECTED=0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING

}OC1B_Mode_type;


typedef enum{
	RISING,
	FALLING
}ICU_Edge_type;




void Timer1_InputCaptureEdge(ICU_Edge_type edge);
void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler,OC1A_Mode_type oc1a_mode,OC1B_Mode_type oc1b_mode);

void Timer1_ICU_InterruptEnable(void);
void Timer1_ICU_InterruptDisable(void);
void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);
void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);
void Timer1_OCB_InterruptEnable(void);
void Timer1_OCB_InterruptDisable(void);
void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void));

#endif /* TIMERS_H_ */
