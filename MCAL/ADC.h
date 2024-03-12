/*
 * ADC.h
 *
 * Created: 9/2/2021 10:34:40 AM
 *  Author: Dell
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "UTILS.h"
#include "STDTYPES.h"
#include "MEMOMAP.h"

typedef enum
{
	VREF_AVCC,
	VREF_AREF,
	VREF_256
}ADC_vref_Type;
typedef enum
{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128
}ADC_scaler_type;
typedef enum
{
	ch_0=0,
	ch_1,
	ch_2,
	ch_3,
	ch_4,
	ch_5,
	ch_6,
	ch_7
}ADC_channel_type;


void ADC_Init(ADC_vref_Type vref,ADC_scaler_type scaler);
u16 ADC_Read(ADC_channel_type ch);
#endif /* ADC_H_ */