#include "controlunit.h"
#include <cstring>

Controlunit::Controlunit()
{
	this->mode_ = SPI_MODE_0;
	this->bitsPerWord_ = 8;
	this->speed_ = 1000000;
	this->spifd_ = -1;

	this->initSPI();
}

Controlunit::~Controlunit()
{
	this->killSPI();
}

int Controlunit::readADC(int channel)
{
	unsigned char data[3];
	int resultMoist = 0;
	//Add channel defined as data buffer (if - if else) //
	if (channel == 0)
	{
		data[0] = 1;  //  first byte transmitted -> start bit
		data[1] = 0b10100000; // Use channel 0. 
		data[2] = 0; // third byte transmitted....don't care
	}
	else if (channel == 1)
	{
		data[0] = 1;  //  first byte transmitted -> start bit
		data[1] = 0b11100000; // Use channel 1. 
		data[2] = 0; // third byte transmitted....don't care
	}
	else
	{
		perror("Channel is not valid");
		exit(1);
	}

	int length = sizeof(data);
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

	retVal = ioctl(this->spifd_, SPI_IOC_MESSAGE(length), &spi);

	if (retVal < 0) 
	{
		perror("Problem transmitting spi data..ioctl");
		exit(1);
	}

	resultMoist = (data[1] << 8) & 0b111100000000; //merge data[1] & data[2] to get result
	resultMoist |= (data[2] & 0xff);

	return retVal;
}

void Controlunit::printADC()
{
	int ch0, ch1; 
	ch0 = this->readADC(0);
	ch1 = this->readADC(1);

	cout << "CH0: " << ch0 << " | Ch1: " << ch1 << endl;
}

int Controlunit::initSPI()
{
	int statusVal = -1;

	this->spifd_ = open("/dev/spidev0.0", O_RDWR);
	if (this->spifd_ < 0)
	{
		perror("could not open SPI device");
		exit(1);
	}

	statusVal = ioctl(this->spifd_, SPI_IOC_WR_MODE, &(this->mode_));
	if (statusVal < 0) 
	{
		perror("Could not set SPIMode (WR)...ioctl fail");
		exit(1);
	}

	statusVal = ioctl(this->spifd_, SPI_IOC_RD_MODE, &(this->mode_));
	if (statusVal < 0) 
	{
		perror("Could not set SPIMode (RD)...ioctl fail");
		exit(1);
	}

	statusVal = ioctl(this->spifd_, SPI_IOC_WR_BITS_PER_WORD, &(this->bitsPerWord_));
	if (statusVal < 0) 
	{
		perror("Could not set SPI bitsPerWord (WR)...ioctl fail");
		exit(1);
	}

	statusVal = ioctl(this->spifd_, SPI_IOC_RD_BITS_PER_WORD, &(this->bitsPerWord_));
	if (statusVal < 0) 
	{
		perror("Could not set SPI bitsPerWord (RD)...ioctl fail");
		exit(1);
	}

	statusVal = ioctl(this->spifd_, SPI_IOC_WR_MAX_SPEED_HZ, &(this->speed_));
	if (statusVal < 0) 
	{
		perror("Could not set SPI speed (WR)...ioctl fail");
		exit(1);
	}

	statusVal = ioctl(this->spifd_, SPI_IOC_RD_MAX_SPEED_HZ, &(this->speed_));
	if (statusVal < 0) 
	{
		perror("Could not set SPI speed (RD)...ioctl fail");
		exit(1);
	}
	return statusVal;
}

int Controlunit::killSPI()
{
	int statusVal = -1;

	statusVal = close(this->spifd_);
	if (statusVal < 0) 
	{
		perror("Could not close SPI device");
		exit(1);
	}
	return statusVal;
}
