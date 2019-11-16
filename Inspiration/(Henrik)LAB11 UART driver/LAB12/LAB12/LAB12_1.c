/*
 * LAB12_1.c
 *
 * Created: 24-04-2018 10:34:11
 *  Author: Henrik
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "uart_int.h"
#include "led.h"

int main (void)
{
	InitUART(9600, 8, 'N', 1);
	
	sei(); 
	
	initLEDport();
		
	while(1)
	{}	
	
	return 0;

}

ISR(USART0_RX_vect)
{
	char x = UDR0;
	
	if ((x >= '0') && (x <= '7'))
	{
		toggleLED(x-'0');	
		SendString("LED nr. ");
		SendInteger(x-'0');
		SendString(" er toggled\n");	
	}
}