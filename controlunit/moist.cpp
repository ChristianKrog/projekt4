#include "moist.h"
#include <cstring>

int Moist::getMoist(int sensorID) 
{
	unsigned char data[3];
	int resultMoist = 0, length = 0;
	
	if (sensorID == 0)
	{
		data[0] = 1;  //  first byte transmitted -> start bit
		data[1] = 0b10100000; // Use channel 0 on MCP3202
		data[2] = 0; // third byte transmitted....don't care
	}
	else if (sensorID == 1)
	{
		data[0] = 1;  //  first byte transmitted -> start bit
		data[1] = 0b11100000; // Use channel 1 on MCP3202
		data[2] = 0; // third byte transmitted....don't care
	}
	else
	{
		perror("Sensor does not exist");
		exit(1);
	}

	length = sizeof(data);
	struct spi_ioc_transfer spi[length];
	memset(&spi, 0, sizeof(spi));
	int i = 0;
	int retVal = -1;

	// one spi transfer for each byte

	for (i = 0; i < length; i++)
	{
		spi[i].tx_buf = (unsigned long)(data + i); // transmit from "data"
		spi[i].rx_buf = (unsigned long)(data + i); // receive into "data"
		spi[i].len = sizeof(*(data + i));
		spi[i].delay_usecs = 0;
		spi[i].speed_hz = this->speed_;
		spi[i].bits_per_word = this->bitsPerWord_;
		spi[i].cs_change = 0;
	}

	retVal = ioctl(this->spifd, SPI_IOC_MESSAGE(length), &spi);

	if (retVal < 0)
	{
		perror("Problem transmitting spi data..ioctl");
		exit(1);
	}

	resultMoist = (data[1] << 8) & 0b111100000000; //merge data[1] & data[2] to get result
	resultMoist |= (data[2] & 0xff);

	return resultMoist;
}

void Moist::printMoist()
{
	int ch0, ch1;
	ch0 = this->getMoist(0);
	ch1 = this->getMoist(1);

	cout << "CH0: " << ch0 << " | Ch1: " << ch1 << endl;
}
}
