/********************************************
* MSYS, LAB 11                              *
* Test program for Mega2560 UART driver.    *
* Using UART 0.                             *
*                                           *
* Henning Hargaard 4/11 2015                *
*********************************************/
#include <avr/io.h>
#include "uart.h"
#include "led.h"

int main()
{
  char tegn;
  char TestStreng[40] = "This string is stored in SRAM memory\r\n";

  // Initialize LED port
  initLEDport();
  // Initialize UART
  // Important : Also other Baud Rates, Data Bits and Parity should be tested
  // Corresponding changes has to be made in the terminal program used
  // for the test
  InitUART(9600, 8, 'N');

  while (1)
  {
    // Testing SendChar
    writeAllLEDs(1);
    SendChar('A');
    SendChar('B');
    SendChar('C');
    SendChar('\r');
    SendChar('\n');

    // Testing ReadChar() : Read and echo
    writeAllLEDs(2);
    tegn = ReadChar();
    SendChar(tegn);
    SendChar('\r');
    SendChar('\n');

    // Testing CharReady() : Wait, read and echo
    writeAllLEDs(3);	
    while ( !CharReady() )
    {}
    SendChar( ReadChar() );
    SendChar('\r');
    SendChar('\n');

    // Sending string stored in Flash (constant string)
    writeAllLEDs(4);
    SendString("This string is stored as a constant in flash memory\r\n");

    // Sending string stored in SRAM (modify-able string)
    writeAllLEDs(5);
    SendString(TestStreng);

    // Testing SendInteger()
    writeAllLEDs(6);
    SendInteger(12345); //Positive number
    SendChar('\r');
    SendChar('\n');
    SendInteger(-1000); //negative number
    SendChar('\r');
    SendChar('\n');
  }
}