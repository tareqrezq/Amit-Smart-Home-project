

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#include <avr/io.h>


//	Keypad port Configuration
#define KEYPAD_PORT_DIR		DDRA
#define KEYPAD_PORT_OUT		PORTA
#define KEYPAD_PORT_IN		PINA

//	Keypad Configuration for Rows & ColumnS
#define	N_ROW 4
#define N_COL 4

#endif
