#include "dht22.h"

void DHT22::sendTemp()
{
	char string[8];
	sprintf(string, %.0f, temp_)
	// Repeat until zero-termination
	while (*string != 0)
	{
		// Send the character pointed to by "Streng"
		sendCharUART(*string);
		// Advance the pointer one step
		string++;
	}
}

float DHT22::getTemp()
{
	
	return temp_;
}

void DHT22::sendCharUART(char something)
{
	// Wait for transmitter register empty (ready for new character)
	while ((UCSR0A & (1 << 5)) == 0)
	{
	}
	// Then send the character
	UDR0 = something;
}
