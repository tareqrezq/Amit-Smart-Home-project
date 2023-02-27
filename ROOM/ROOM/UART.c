#include "UART.h"
#define BAUD_PRESCALE ((F_CPU / (UART_BAUDRATE * 8UL))-1)

void USART_Init (void)					// Function to initialize the UART
{
	// Enable Double speed mode

	UCSRA = (1<<U2X);  

	/*
	 * Disable for RX complete interrupt
	 * Disable for TX complete interrupt
	 * Disable for UDR empty register interrupt
	 * RXB8 & TXB not Used
	 * Enable receiver (RXEN = 1)
	 * Enable Transmitter (TXEN = 1)
	 */
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*
	 * URSEL = 1 to select UCSRC register
	 * URSEL = 0 for Asynchronous
	 * UPM0:1 = 00 (Disable Parity)
	 * USBS = 0 for 1 stop bit
	 * UCSZ1:0 = 1 (8-Bit data length)
	 * UCPOL = 0  (Used with Synchronous mode Only)
	 */

	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1); 

	// Set value of UBRR register with defined baudrate (9600)
	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;

}

void USART_sendByte (u8 data)			// Function to send data byte
{
	while (BIT_IS_CLEAR(UCSRA,UDRE));	//Polling until UDR register is empty and ready to take data
	UDR = data;						    //Set data to UDR register

}

u8 USART_receiveByte (void)				// Function to receive data byte
{
	while (BIT_IS_CLEAR(UCSRA,RXC));	//Polling until UDR register is full with data
	return UDR;							// Return the data from UDR register
}


