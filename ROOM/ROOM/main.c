/*
 * room.c
 *
 * Created: 2022-02-13 8:19:04 PM
 * Author : Ahmed Elnakeeb
 */ 


#include "DIO.h"
#include "UART.h"

int main()
{
	USART_Init();
	Set_PinDir(PORT_B,Pin_0,OUTPUT);
	Set_PinDir(PORT_B,Pin_1,OUTPUT);
	Set_PinDir(PORT_C,Pin_0,OUTPUT);
	Set_PinDir(PORT_C,Pin_1,OUTPUT);
	Set_PinDir(PORT_C,Pin_2,OUTPUT);

	
	
	while(1)
	{

		if(USART_receiveByte() == 'H')			// Alarm On
		{
			Set_PinLevel(PORT_B,Pin_0,HIGH);
			Set_PinLevel(PORT_B,Pin_1,HIGH);
			Set_PinLevel(PORT_C,Pin_2,HIGH);
			Set_PinLevel(PORT_C,Pin_1,HIGH);
		}
		else if(USART_receiveByte() == 'F')		// Fan On
		{
			Set_PinLevel(PORT_B,Pin_0,HIGH);
			Set_PinLevel(PORT_B,Pin_1,LOW);
			Set_PinLevel(PORT_C,Pin_1,HIGH);
			
		}
		else                                    // Alarm Off
		{
			Set_PinLevel(PORT_B,Pin_0,LOW);
			Set_PinLevel(PORT_B,Pin_1,LOW);
			Set_PinLevel(PORT_C,Pin_2,LOW);
			
		}

		if(USART_receiveByte() == 'L')			// Led On
		{
		  Set_PinLevel(PORT_C,Pin_0,HIGH);
		
		}
		else
		{
			Set_GroupLevel(PORT_C,0x00);
		}
	}
}


