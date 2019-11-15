#include "controlunit.h"
#include <cstring>

Controlunit::Controlunit()
{
	//Set SPI parameters
	this->mode_ = SPI_MODE_0;
	this->bitsPerWord_ = 8;
	this->speed_ = 1000000;
	this->spifd_ = -1;
	this->initSPI();
	
	//////////////////UART////////////////
	//this->initUART();
}

Controlunit::~Controlunit()
{
	this->killSPI();
	this->killUART();
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

/*
int Controlunit::initUART()
{
	port(io, "/dev/ttyS0");
	int baudrate = 57600

	port.set_option(asio::serial_port_base::baud_rate(baudrate));
	   
	//Stopbit = 1
	asio::serial_port_base::stop_bits 	Stop(asio::serial_port_base::stop_bits::one);
	port.set_option(Stop);

	//Parity = 0
	asio::serial_port_base::parity 		pari(asio::serial_port_base::parity::none);	//chooses if parity bit is used
	port.set_option(pari);
	
	port.close();

	return 0;
}
*/
