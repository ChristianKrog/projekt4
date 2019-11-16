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
   // <---- Skriv din kode her  
}

/*************************************************************************
Returns 0 (FALSE), if the UART has NOT received a new character.
Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   // <---- Skriv din kode her
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
   // <---- Skriv din kode her
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter:
  Tegn: Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
   // <---- Skriv din kode her
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
  Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
   // <---- Skriv din kode her
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
   // <---- Skriv din kode her
}

/************************************************************************/