

#include "KeyPad.h"
static u8 keys_array[4][4]={{'7','8','9','/'},
{'4','5','6','*'},
{'1','2','3','-'},
{'c','0','=','+'}};

u8 Keypad_getentry(void)
{
	u8 r,c,key=default_key;
	DIO_WritePin(first_out,HIGH);
	DIO_WritePin(first_out+1,HIGH);
	DIO_WritePin(first_out+2,HIGH);
	DIO_WritePin(first_out+3,HIGH);
	for (r=0;r<4;r++)
	{
		DIO_WritePin(first_out+r,LOW);
		for (c=0;c<4;c++)
		{
			if (!DIO_ReadPin(first_in+c)/*or DIO_READPIN(First_in+c)==LOW*/)
			{
				key=keys_array[r][c];
				while(!DIO_ReadPin(first_in+c));
			}
		}
		DIO_WritePin(first_out+r,HIGH);
	}
	return key;
}


/*
x=Keypad_getentry();
if (x!=default_key)
{
	if ((x<='9')&&(x>='0'))
	{
		LCD_WriteChar(x);
		num=(num*10)+(x-'0');
	}
	if (x=='c')
	{
		LCD_Clear();
		num=num1=num2=r=0;
	}
	if ((x=='/')||(x=='*')||(x=='-')||(x=='+'))
	{
		if (c==1)
		{
			num1=r;
			num=0;
			c=2;
			y=x;
			LCD_WriteChar(x);
		}
		else if (c==0)
		{
			c=1;
			y=x;
			LCD_WriteChar(x);
			num1=num;
			num=0;
		}
		else if (c==2)
		{
			num1=r;
			num=0;
			c=0;
			y=x;
			LCD_WriteChar(x);
		}
	}
	if (x=='=')
	{
		num2=num;
		num=0;
		LCD_WriteChar(x);
		switch (y)
		{
			case '/' :
			r=num1/num2;
			break;
			case '*' :
			r=num1*num2;
			break;
			case '+' :
			r=num1+num2;
			break;
			case '-' :
			r=num1-num2;
			break;
		}
		LCD_WriteNumber(r);
	}
}
*/