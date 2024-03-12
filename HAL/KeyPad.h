
#include "STDTYPES.h"
#include "DIO_INTERFACE.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_




#define first_out PIND_0
#define first_in  PIND_4
#define default_key  '.'


u8 Keypad_getentry(void);



#endif /* KEYPAD_H_ */