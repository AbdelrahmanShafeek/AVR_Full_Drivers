 

#include "STDTYPES.h"
#include "DIO_INTERFACE.h"

#ifndef  LCD_H_
#define  LCD_H_


#define  F_CPU  8000000UL

#include <util/delay.h>

#define   _4_BIT  0
#define   _8_BIT  1


#define   LCD_MODE    _8_BIT

/*for 8 bit mode*******/
#define   LCD_PORT     PC
/*for 4 bit mode*******/

#define   D4		   PINA_4
#define   D5		   PINA_5
#define   D6		   PINA_6
#define   D7		   PINA_7

#define   RS           PINA_0
#define   RW           PINA_1
#define   EN           PINA_2



/****************************************************************/

void LCD_WriteCommand(u8 command);
void LCD_WriteData(u8 data);

void LCD_Init(void);
void LCD_Clear(void);
void LCD_Create_Character(u8 *Pattern,u8 Location);
void LCD_WriteChar(u8 ch);
void LCD_WriteString(u8*str);
void LCD_WriteNumber(s64  num);
void LCD_GoTo(u8 Line, u8 x);
void LCD_Go_To(u8 Line, u8 x);
void LCD_WriteNumberInBinary(u8 num);
void LCD_WriteNumber_4D(u16 num);

#endif /* LCD_H_ */









/*
Memory Map
Pattern No.	CGRAM Address (Acg)
1	0x00 – 0x07
2	0x08 – 0x0F
3	0x10 – 0x17
4	0x18 – 0x1F
5	0x20 – 0x27
6	0x28 – 0x2F
7	0x30 – 0x37
8	0x38 – 0x3F


No.	Instruction	                                           Hex	                Decimal
1	Function Set: 8-bit, 1 Line, 5×7 Dots	               0x30					48
2	Function Set: 8-bit, 2 Line, 5×7 Dots	               0x38					56
3	Function Set: 4-bit, 1 Line, 5×7 Dots	               0x20					32
4	Function Set: 4-bit, 2 Line, 5×7 Dots	               0x28					40
5	Entry Mode	                                           0x06					6
6	Display off Cursor off
    (clearing display without clearing DDRAM content)	   0x08	                8
7	Display on Cursor on	                               0x0E	                14
8	Display on Cursor off	                               0x0C	                12
9	Display on Cursor blinking	                           0x0F	                15
10	Shift entire display left	                           0x18	                24
12	Shift entire display right	                           0x1C	                30
13	Move cursor left by one character	                   0x10	                16
14	Move cursor right by one character	                   0x14	                20
15	Clear Display (also clear DDRAM content)	           0x01	                1
16	Set DDRAM address or coursor position on display	      0x80+add*	128+add*
17	Set CGRAM address or set pointer to CGRAM location	      0x40+add**64+add**
*/