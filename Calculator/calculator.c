/*
 * calculator.c
 *
 *  Created on: 6 Oct 2023
 *      Author: Zeyad El-banna
 */
#include"gpio.h"
#include"lcd.h"
#include"keypad.h"
#include"common_macros.h"
#include<util/delay.h>
int main(void)
{
	LCD_init();
	volatile sint32 num = 0;
	volatile sint16 temp;
	volatile float64 result ;
	volatile sint32 num2 = 0;
	volatile uint8 operator ;
	char str[] = "Calculator";
	LCD_displayStringRowColumn(0,3,str);
	_delay_ms(2000);
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	volatile uint8 cnt = 1 ;
	while(1)
	{

		_delay_ms(500);
		temp = KEYPAD_getPressedKey();
		if ((temp != '+') && (temp != '-') && (temp != '*') && (temp != '%') && (temp != '=') && (temp != 13))
		{
			if(operator == '=')
			{
				LCD_clearScreen();
				operator = '!';
			}
			switch(cnt)
			{
			case 1 : num = temp ;
			         cnt++;
			         break;
			case 2 : num = (num*10) + temp ;
			         cnt++;
					 break;
			case 3 : num = (num*10) + temp ;
			         cnt ++ ;
					 break;
			case 4 : num = (num*10) + temp ;
					 cnt ++ ;
					 break;
			case 5 : num = (num*10) + temp ;
					 break;

			}

			LCD_intgerToString((int)temp);

		}
		else if( temp == '=' )
		{
			switch(operator)
			{
			case '+' : result = num + num2 ;
			           break;
			case '-' : result = num2 - num;
					   break;
			case '*' : result = num * num2;
					   break;
			case '%' : result = (float32)num2 / num;
					   break;
			default : result = num ;
			}
			cnt = 1;
			LCD_displayCharacter(temp);
			LCD_floatToString(result);
			result = 0 ;
			num2 = 0 ;
			num = 0 ;
			operator = temp ;
		}
		else if((temp == '+') || (temp == '-') || (temp == '*') || (temp == '%'))
		{
			cnt = 1;
			num2 = num ;
			num = 0;
			operator = temp ;
			LCD_displayCharacter(temp);
		}
		else if (temp == 13)
		{
		    LCD_clearScreen();
		    cnt = 1;
		    num2 = 0 ;
		    num = 0;
		    result = 0;
		}
	}
	return 0 ;
}

