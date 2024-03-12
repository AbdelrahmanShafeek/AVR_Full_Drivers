

#ifndef STEPPER_H_
#define STEPPER_H_

#include "STDTYPES.h"
#include "UTILS.h"
#include "DIO_INTERFACE.h"

#define    BIBOLER    1
#define    UNIPOLER   0


#define    MOTOR_TYPE     UNIPOLER

/********STEPPER PIN CONFIGRATION***********/
#define COIL1A       PINB_3
#define COIL1B       PINB_4
#define COIL2A       PINB_5
#define COIL2B       PINB_6







#define  DELAY   500

void STEPPER_cw(void);
void STEPPER_ccw(void);

void STEPPER_cw(void);
void STEPPER_ccw(void);
void STEPPER_cw_halfstep(void);


void STTEPER_CW(u8 rev);
void STTEPER_CW_ANGLE(u16 angle);

#endif /* STEPPER_H_ */