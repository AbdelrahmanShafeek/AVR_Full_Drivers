

#include "LCD.h"

/*************Initializing Specific LCD*********************/

#if (LCD_MODE==_8_BIT)      //sending instruction to the lcd
void LCD_WriteCommand(u8 command)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(RW,LOW);
	DIO_WritePort(LCD_PORT,command);
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);
	
}

void LCD_WriteData(u8 data)  //sendind data to be printed on lcd
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(RW,LOW);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(2);
	DIO_WritePin(EN,LOW);
	_delay_ms(2);	
}
void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x38);		//select 8 bit mode,font 5*7,select 2 lines
	_delay_ms(1);
	LCD_WriteCommand(0x0c);		//cursor  0x0c,0x0e,0x0f
	_delay_ms(1);
	LCD_WriteCommand(0x01);		//clear lcd
	_delay_ms(2);
	LCD_WriteCommand(0x06);		//DDRAM address increase
	_delay_ms(1);
	
}
#elif (LCD_MODE==_4_BIT)
void LCD_WriteCommand(u8 command)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(RW,LOW);
	DIO_WritePin(D7,READ_BIT(command,7));
	DIO_WritePin(D6,READ_BIT(command,6));
	DIO_WritePin(D5,READ_BIT(command,5));
	DIO_WritePin(D4,READ_BIT(command,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(command,3));
	DIO_WritePin(D6,READ_BIT(command,2));
	DIO_WritePin(D5,READ_BIT(command,1));
	DIO_WritePin(D4,READ_BIT(command,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(RW,LOW);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
void LCD_Init(void)
{
	_delay_ms(50); 
	LCD_WriteCommand(0x02);
	_delay_ms(1);
	LCD_WriteCommand(0x28);//select 4bit mode,font 5*7,select 2 lines
	_delay_ms(1);
	LCD_WriteCommand(0x0c);//cursor  0x0c,0x0e,0x0f
	_delay_ms(1);
	LCD_WriteCommand(0x01);//clear lcd
	_delay_ms(2);
	LCD_WriteCommand(0x06);//DDRAM address increase
	_delay_ms(1);
	LCD_WriteCommand(0x80);
}
#endif






/****************************************************************************************/


void LCD_WriteChar(u8 ch)
{
	LCD_WriteData(ch);
}


void LCD_WriteString(u8*str)
{
	u8 i=0 ;
	while(str[i])
	{
		LCD_WriteData(str[i]);
		i++ ;
	}
}

void LCD_WriteNumber(s64 num)
{
	u8 rem,i=0,j=0,arr[16];
	if (num==0)
	{
		LCD_WriteData('0');
	}
	if (num<0)
	{
		LCD_WriteData('-');
		num=num*(-1) ;
	}
	
	
	while (num>0)
	{
		rem=num%10;
		arr[i]=rem+'0';
		i++;
		num=num/10;
	}
	for (j=i;j>0;j--)
	{
		LCD_WriteData(arr[j-1]);
	}
	
	
}

void LCD_WriteNumberInBinary(u8 num)
{
	s8 i,flag=0;
	for(i=7;i>=0;i--)
	{
		if (((num>>i)&1)==1)
		{
			flag=1;
		}
		if (flag==1)
		{
				LCD_WriteData(((num>>i)&1)+'0');
		}
	
	}
}



void LCD_GoTo(u8 Line, u8 x)
{
	u8 command=0x80;
	if (Line==1)
	{
		LCD_WriteCommand(command/*or 0x80 */+x);
	}
	else
	{
		LCD_WriteCommand(command/*or 0x80 */+0x40+x);
	}
}

void LCD_Create_Character( u8*pattern , u8  address)
{
	u8 i;
	LCD_WriteCommand(0x40+(address*8));
	for (i=0;i<8;i++)
	{
		LCD_WriteData(pattern[i]);
	}
	
}  



/*
void LCD_Create_Character(u8 *Pattern,u8 Location) {

	u8 iLoop=0;

	LCD_WriteCommand(0x40+(Location*8)); //Send the Address of CGRAM
	for(iLoop=0;iLoop<8;iLoop++)
	LCD_WriteData(Pattern[iLoop]);      //Pass the bytes of pattern on LCD

}
*/
void LCD_Clear(void)
{

	LCD_WriteCommand(0x01);

}
void LCD_Go_To(u8 Line, u8 x)
{
	if(0 == Line)
	{
		if ( x <=15)
		{
			LCD_WriteCommand(0x80 + x);
		}
	}
	else if (1 == Line)
	{
		if ( x <=15)
		{
			LCD_WriteCommand(0xC0 + x);
		}
	}
}


void LCD_WriteNumber_4D(u16 num)
{
	    LCD_WriteData(((num%10000)/1000)+'0');
		LCD_WriteData(((num%1000)/100)+'0');
		LCD_WriteData(((num%100)/10)+'0');
		LCD_WriteData(((num%10)/1)+'0');
} 
