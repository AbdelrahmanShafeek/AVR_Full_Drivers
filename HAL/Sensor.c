

#include "Sensor.h"
#include "STDTYPES.h"



u16 POT_volt_Read(void) //GETTING THE POTTENTIOMETER RESESTANCE VOLT
{
	u16 adc=ADC_Read(POT_ch);
	u16 volt=((u32)5000*adc)/1024;
	return volt ;
};



u16 TEMP_Read(void) //GETTING LM35 READ
{
	u16 adc=ADC_Read(Lm35);
	u16 volt=((u32)5000*adc)/1024;
	u16 temp=volt;
	return temp;
}


u16 POT_Read(void) //GETTING THE POTTENTIOMETER RESESTANCE PERCENT
{
	u16 adc=ADC_Read(POT_ch);
	u16 volt=((u32)5000*adc)/1024;
	volt=volt/50;
	return volt ;
}


