#include "STDTYPES.h"
#include "ADC.h"

#ifndef INCFILE1_H_
#define INCFILE1_H_



#define  POT_ch    ch_0
#define  Lm35	   ch_1

u16 POT_volt_Read(void);
u16 TEMP_Read(void);
u16 POT_Read(void);

#endif /* INCFILE1_H_ */