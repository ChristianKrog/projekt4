#include "temperature.h"

Temperature::Temperature()
{
	this->initDHT();
}

Temperature::~Temperature()
{
	
}

int Temperature::getTemp()
{
	int MAX_TIMINGS = 85;
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	int data[5] = { 0, 0, 0, 0, 0 };
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	/* detect change and read data */
	for (i = 0; i < MAX_TIMINGS; i++)
	{
		counter = 0;
		while (digitalRead(pinDHT_) == laststate)
		{
			counter++;
			usleep(1);
			if (counter == 255)
			{
				break;
			}
		}
		laststate = digitalRead(pinDHT_);

		if (counter == 255)
			break;

		/* ignore first 3 transitions */
		if ((i >= 4) && (i % 2 == 0))
		{
			/* shove each bit into the storage bytes */
			data[j / 8] <<= 1;
			if (counter > 16)
				data[j / 8] |= 1;
			j++;
		}
	}

	float h = (float)((data[0] << 8) + data[1]) / 10;
		if ( h > 100 )
		{
			h = data[0];	
		}

	float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
	
	if ( data[2] & 0x80 )
	{
		c = -c;
	}	
	
	return c;
}

void Temperature::initDHT()
{	
	wiringPiSetup();
	//pull pin down for 18 milliseconds 
	pinMode(pinDHT_, OUTPUT);
	digitalWrite(pinDHT_, LOW);
	usleep(18);

	/* prepare to read the pin */
	pinMode(pinDHT_, INPUT);
}
