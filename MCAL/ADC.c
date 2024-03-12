 

#include "ADC.h"

static  u8    Read_Flag=0;


void ADC_Init(ADC_vref_Type vref,ADC_scaler_type scaler)
{
	/**Vref**/
	switch(vref)
	{
		case VREF_AVCC:
		SET_BIT(ADMUX_PR,REFS0);
		CLEAR_BIT(ADMUX_PR,REFS1);
		break;
		case VREF_AREF:
		CLEAR_BIT(ADMUX_PR,REFS0);
		CLEAR_BIT(ADMUX_PR,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX_PR,REFS0);
		SET_BIT(ADMUX_PR,REFS1);
		break;
		
	}
	
	/**clock**/
	ADCSRA_PR=ADCSRA_PR&0xf8;
	scaler=scaler&0x07;
	ADCSRA_PR=ADCSRA_PR&scaler;
	/******adjust right****/
	CLEAR_BIT(ADMUX_PR,ADLAR);
	
	/**ENABLE*/
	SET_BIT(ADCSRA_PR,ADEN);
}

u16 ADC_Read(ADC_channel_type ch)
{
	//select channel
	ADMUX_PR=ADMUX_PR&0XE0; //0b11100000
	ADMUX_PR=ADMUX_PR|ch;
	//start conversion
	SET_BIT(ADCSRA_PR,ADSC);
	while(READ_BIT(ADCSRA_PR,ADSC)); //polling(BUSY WAIT) until adc end conversion
	//u16 adc=ADCL|((U16)ADCH<<8);
	return ADC_PR;
}

void ADC_StartConvergion(ADC_channel_type ch)
{
	if (Read_Flag==0)
	{
		//select channel
		ADMUX_PR=ADMUX_PR&0XE0; //0b11100000
		ADMUX_PR=ADMUX_PR|ch;
		//start conversion
		SET_BIT(ADCSRA_PR,ADSC);
		Read_Flag=1;
	}
	
}

u16 ADC_GetRead(void)
{
	while(READ_BIT(ADCSRA_PR,ADSC)); //polling(BUSY WAIT) until adc end conversion
	//u16 adc=ADCL|((U16)ADCH<<8);
	Read_Flag=0;
	return ADC_PR;
}

u8 ADC_GetReadNoBlock(u16*pdata)//call in (IF CONDITION) AND GIVE IT AN ADRESS OF VARIABLE
{
	if(READ_BIT(ADCSRA_PR,ADSC)) //polling(PERIODIC CHICKING) until adc end conversion
	{
		//u16 adc=ADCL|((U16)ADCH<<8);
		*pdata=ADC_PR;
		Read_Flag=0;
		return 1;
	}
	else
	{
		return 0;
	}
}
