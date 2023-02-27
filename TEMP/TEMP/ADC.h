

#ifndef ADC_H_
#define ADC_H_

#include "Macros.h"
#include "Std_Types.h"
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "DIO.h"



void ADC_Init(void);                              //function to intialize ADC
u16 ADC_readChannel (u8 channel);                 //function to read data from specific channel




#endif /* MCAL_ADC_ADC_H_ */
