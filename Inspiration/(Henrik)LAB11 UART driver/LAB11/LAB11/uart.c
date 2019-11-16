/************************************************
* "uart.c":                                     *
* Implementation file for Mega2560 UART driver. *
* Using UART 0.                                 *
* Henning Hargaard, 15/11 2016                  *
*************************************************/
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

// Constants
#define XTAL 16000000

/*************************************************************************
USART initialization.
  Asynchronous mode.
  RX and TX enabled.
  No interrupts enabled.
  Number of Stop Bits = 1.
  No Parity.
  Baud rate = Parameter.
  Data bits = Parameter.
Parameters:
  BaudRate: Wanted Baud Rate (300-115200).
  Databits: Wanted number of Data Bits (5-8).
  Parity: 'E' (Even parity), 'O' (Odd parity), otherwise No Parity.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, char Parity)
{
	UBRR0 = 103; //BAUD-rate = 9600, Asynchronous normal mode 
	
	UCSR0A = 0b11100000;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00000110;
}

/*************************************************************************
Returns 0 (FALSE), if the UART has NOT received a new character.
Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   if (RXC0 == 1)
	{
		return 1;		
	} 
	else
	{
		return 0;
	}
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
   if (RXC0 == 1)
   {
	   return UDR0;
   }
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter:
  Tegn: Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
   if(UDRE0 == 1)
   {
	   UDR0 = Tegn;
   }
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
  Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
   while(*Streng !='\0')
   {
		SendChar(*Streng);
		Streng++;
   }
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART. 
Makes use of the C standard library <stdlib.h>.
Parameter:
  Tal: The integer to be converted and sent. 
*************************************************************************/
void SendInteger(int Tal)
{
   char Array[10]; //Ændret fra int array til char array
   
   itoa( Tal, Array, 10 );
   
   SendString(Array);
   
}

/************************************************************************/