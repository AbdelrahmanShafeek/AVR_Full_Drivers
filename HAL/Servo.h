

#ifndef SERVO_H_
#define SERVO_H_

#include "Timers.h"

#define Servo_Pin   OCR1B_PR

void Servo_Init (void);

void Servo_SetAngle (u8 Angle);


#endif /* SERVO_H_ */