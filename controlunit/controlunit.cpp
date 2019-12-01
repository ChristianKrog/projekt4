#include "controlunit.h"
#include <cstring>

Controlunit::Controlunit()
{
	initI2C();
}

Controlunit::~Controlunit()
{
	killI2C();
}

void Controlunit::initSPI()
{
	int fdVal;
	unsigned char spiMode = SPI_MODE_0;
	bitsPerWord_ = 8;
	speed_ = 1000000;

	spifd_ = open("/dev/spidev0.0", O_RDWR);
	if (spifd_ == -1)
	{	
		cout << "Could not open SPI device: " << strerror(errno) << endl;
		exit(1);
	}

	fdVal = ioctl(spifd_, SPI_IOC_WR_MODE, &spiMode);
	if (fdVal == -1)
	{
		cout << "Could not set SPI mode: " << strerror(errno) << endl;
		exit(1);
	}

	fdVal = ioctl(spifd_, SPI_IOC_RD_MODE, &spiMode);
	if (fdVal == -1)
	{
		cout << "Could not read SPI mode: " << strerror(errno) << endl;
		exit(1);
	}

	fdVal = ioctl(spifd_, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord_);
	if (fdVal == -1)
	{
		cout << "Could not set SPI bits per word: " << strerror(errno) << endl;
		exit(1);
	}

	fdVal = ioctl(spifd_, SPI_IOC_RD_BITS_PER_WORD, &bitsPerWord_);
	if (fdVal == -1)
	{
		cout << "Could not read SPI bits per word " << strerror(errno) << endl;
		exit(1);
	}

	fdVal = ioctl(spifd_, SPI_IOC_WR_MAX_SPEED_HZ, &speed_);
	if (fdVal == -1)
	{
		cout << "Could not set SPI speed: " << strerror(errno) << endl;
		exit(1);
	}

	fdVal = ioctl(spifd_, SPI_IOC_RD_MAX_SPEED_HZ, &speed_);
	if (fdVal == -1)
	{
		cout << "Could not read SPI speed: " << strerror(errno) << endl;
		exit(1);
	}
}

void Controlunit::killSPI()
{
	int fdVal = -1;

	fdVal = close(spifd_);
	if (fdVal < 0) 
	{
		cout << "Could not close SPI device: " << strerror(errno) << endl; 
		exit(1);
	}
}

void Controlunit::initI2C()
{
	i2cfd_ = open("/dev/i2c-1", O_RDWR);

	if (i2cfd_ == -1) 
	{
		cout << "Filedirectory error: " << strerror(errno) << endl;
		exit(1);
	}
}

void Controlunit::killI2C()
{
	int fdVal;

	fdVal = close(i2cfd_);
	if (fdVal == -1)
	{
		cout << "Could not close I2C device: " << strerror(errno) << endl;
		exit(1);		
	}
}

int Controlunit::readI2C(unsigned char address)
{
	char BUF[2];
	int readVal; 
	int fdVal;
	
	ioctl(i2cfd_, 0x0703, address); 
	fdVal = read(i2cfd_, BUF, 2);

	if (fdVal == -1) 
	{
		cout << "Read error: " << strerror(errno) << endl;
	}
	else 
	{
		BUF[fdVal] = 0;
		readVal = BUF[0];
	}
	
	return readVal;
}

void Controlunit::sendI2C(unsigned char address, unsigned char choosePWM, unsigned char dutycycle)
{
	unsigned char buffer[3];
	buffer[0] = 0; //First data sent is dataPtr. Always 0
	buffer[1] = (unsigned char)choosePWM;
	buffer[2] = (unsigned char)dutycycle;
	int fdVal;
	
	ioctl(i2cfd_, 0x0703, address);

	fdVal = write(i2cfd_, buffer, 3);

	if (fdVal == -1) 
	{
		cout << "Error write: " << strerror(errno) << endl;
	}
	else 
	{
		//cout << "succes " << sizeof(buffer) << endl; 
	}
}
