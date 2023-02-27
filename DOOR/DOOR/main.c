#include <avr/io.h>
#include <avr/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "keypad.h"
#include "keypad_config.h"

int main ()
{
	u8 key;
	u8 mode;
	u32 Saved_Pass = 1234;
	u32 Reversed_Pass = 1432;
	u32 Get_Reversed_Pass = 0;
	u32 Temp_Pass = 0;
	u32 Comp_Pass =  0;
	u8 motor_steps[2] = {6,3};
	Set_GroupDir(PORT_C,0x0F);
	Set_GroupLevel(PORT_C,0xF0);
	LCD_Init ();
	Display_Str_Row_Col(0,2,"Welcome Back ");
	_delay_ms(500);
	Set_PinDir(PORT_D,Pin_0,OUTPUT);
	while(1)
	{
		LCD_CLEAR();
		Display_Str_Row_Col(0,2,"Chose a Mode");
		_delay_ms(500);
		LCD_CLEAR();
		Display_Str("1-Enter Pass");
		Display_Str_Row_Col(1,0,"2-Change Pass");
		mode = Keypad_GetPressedKey();

		// Code to get the Password From the User
		if ( mode == 1)
		{
			LCD_CLEAR();
			Display_Str("Password : ");
			for (u8 i = 0; i<4 ;i++)
			{
				Send_CMD(CURSOR_ON);
				_delay_ms(100);
				Send_CMD(CURSOR_OFF);

				key = Keypad_GetPressedKey();
				if ((key>=0) && (key <=9))
				{
					Integer_TO_String (key);
					_delay_ms(200);
					Display_Str_Row_Col(0,11+i,"*");
				}
				else
				{
					LCD_CLEAR();
					Display_Str_Row_Col(0,1,"Invalid Input");
					_delay_ms(500);
					break;
				}
				Comp_Pass += key;
				Comp_Pass = Comp_Pass * 10;
			}
			Comp_Pass = Comp_Pass / 10;
			_delay_ms(500);
			LCD_CLEAR();
			if (Saved_Pass == Comp_Pass)
			{
				Display_Str("Welcome Back");
				Set_PinLevel(PORT_D,Pin_0,HIGH);
				PORTC = (PORTC & 0xF0) | (motor_steps[1] & 0x0F);  // 90
				_delay_ms(3000);
				PORTC = (PORTC & 0xF0) | (motor_steps[0] & 0x0F);  //   0
				Set_PinLevel(PORT_D,Pin_0,LOW);
				LCD_CLEAR();
				Comp_Pass = 0;
			}
			else if (Reversed_Pass == Comp_Pass)
			{
				Display_Str_Row_Col(0,1,"Calling  122");
				_delay_ms(1000);
				LCD_CLEAR();
				Comp_Pass = 0;
			}
			else
			{
				Display_Str_Row_Col(0,1,"Wrong Password");
				_delay_ms(500);
				LCD_CLEAR();
				Comp_Pass = 0;
			}
		}

		// Code to Change the Password
		else if (mode == 2)
		{
			LCD_CLEAR();
			Display_Str("Old Pass : ");
			for (u8 i = 0; i<4 ;i++)
			{
				Send_CMD(CURSOR_ON);
				_delay_ms(200);
				Send_CMD(CURSOR_OFF);

				key = Keypad_GetPressedKey();
				if ((key>=0) && (key <=9))
				{
					Integer_TO_String (key);
					_delay_ms(200);
					Display_Str_Row_Col(0,11+i,"*");
				}
				else
				{
					LCD_CLEAR();
					Display_Str_Row_Col(0,1,"Invalid Input");
					_delay_ms(500);
					break;
				}
				Comp_Pass += key;
				Comp_Pass = Comp_Pass * 10;
			}
			Comp_Pass = Comp_Pass / 10;
			_delay_ms(500);
			LCD_CLEAR();
			if (Saved_Pass == Comp_Pass)
			{

				Comp_Pass = 0;
				Saved_Pass = 0;
				Reversed_Pass = 0;
				Get_Reversed_Pass = 0;
				Display_Str("New Pass : ");
				Display_Str_Row_Col(1,0,"Just Numbers");
				for (u8 i = 0; i<4 ;i++)
				{
					Send_CMD(CURSOR_ON);
					_delay_ms(200);
					Send_CMD(CURSOR_OFF);

					key = Keypad_GetPressedKey();
					if ((key>=0) && (key <=9))
					{
						Go_To_Row_Col(0,11+i);
						Integer_TO_String (key);
						_delay_ms(200);
						Display_Str_Row_Col(0,11+i,"*");
					}

					Saved_Pass += key;
					Saved_Pass = Saved_Pass * 10;
				}
				Saved_Pass = Saved_Pass / 10;
				Temp_Pass = Saved_Pass;
				while (Temp_Pass > 0)
				{
					Get_Reversed_Pass = Temp_Pass % 10;
					Reversed_Pass = (Reversed_Pass * 10) + Get_Reversed_Pass;
					Temp_Pass = Temp_Pass / 10;
				}
				_delay_ms(500);
				LCD_CLEAR();
				Display_Str("Password changed");
				_delay_ms(500);
				LCD_CLEAR();
			}
			else
			{
				Display_Str_Row_Col(0,1,"Wrong Password");
				_delay_ms(500);
				LCD_CLEAR();
				Comp_Pass = 0;
			}
		}
		else
		{
			LCD_CLEAR();
			Display_Str_Row_Col(0,1,"Invalid Input");
			_delay_ms(500);
		}
	}
}
