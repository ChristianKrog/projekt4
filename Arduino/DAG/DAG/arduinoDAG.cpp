#include "arduinoDAG.h"

arduinoDAG::arduinoDAG()
{
	this->baudrate_ = 9600; //Set baudrate here
	this->databit_ = 8; //Set number of databits here
	this->initUART();
}

arduinoDAG::~arduinoDAG()
{
}

void arduinoDAG::initUART()
{
	// "Normal" clock, no multiprocessor mode (= default)
	UCSR0A = 0b00100000;
	// No interrupts enabled
	// Receiver enabled
	// Transmitter enabled
	// No 9 bit operation
	UCSR0B = 0b00011000;
	// Asynchronous operation, 1 stop bit
	// Bit 2 and bit 1 controls the number of data bits
	UCSR0C = (databit_ - 5) << 1;

	// Set Baud Rate according to the parameter BaudRate:
	UBRR0 = 16000000 / (16 * baudrate_) - 1;
}
