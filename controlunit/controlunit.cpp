#include "controlunit.h"
#include <cstring>

Controlunit::Controlunit()
{

}

Controlunit::~Controlunit()
{
	killSPI();
}

int Controlunit::initSPI()
{
	int spiVal;
	this->mode_ = SPI_MODE_0;
	this->bitsPerWord_ = 8;
	this->speed_ = 1000000;
	this->spifd_ = -1;

	this->spifd_ = open("/dev/spidev0.0", O_RDWR);
	if (this->spifd_ == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		exit(1);
	}

	spiVal = ioctl(this->spifd_, SPI_IOC_WR_MODE, &(this->mode_));
	if (spiVal == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		exit(1);
	}

	spiVal = ioctl(this->spifd_, SPI_IOC_RD_MODE, &(this->mode_));
	if (spiVal == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		exit(1);
	}

	spiVal = ioctl(this->spifd_, SPI_IOC_WR_BITS_PER_WORD, &(this->bitsPerWord_));
	if (spiVal == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		exit(1);
	}

	spiVal = ioctl(this->spifd_, SPI_IOC_RD_BITS_PER_WORD, &(this->bitsPerWord_));
	if (spiVal == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		exit(1);
	}

	spiVal = ioctl(this->spifd_, SPI_IOC_WR_MAX_SPEED_HZ, &(this->speed_));
	if (spiVal == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		exit(1);
	}

	spiVal = ioctl(this->spifd_, SPI_IOC_RD_MAX_SPEED_HZ, &(this->speed_));
	if (spiVal == -1)
	{
		cout << "Error: " << strerror(errno) << endl;
		exit(1);
	}
	return spiVal;
}

int Controlunit::killSPI()
{
	int spiVal = -1;

	spiVal = close(this->spifd_);
	if (spiVal < 0) 
	{
		perror("Could not close SPI device");
		exit(1);
	}
	return spiVal;
}

void Controlunit::sendI2C(unsigned char timer, unsigned char dutycycle)
{
	unsigned char buffer[2];
	buffer[0] = (unsigned char)timer;
	buffer[1] = (unsigned char)dutycycle;
	int fd, fdVal;

	fd = open("/dev/i2c-1", O_RDWR);

	if (fd == -1) {
		cout << "Error fd i2c: " << strerror(errno) << endl;
	}

	ioctl(fd, 0x0703, 0x32);
	fdVal = write(fd, buffer, 2);

	if (fdVal == -1) 
	{
		cout << "Error write: " << strerror(errno) << endl;
		close(fd);
	}
	else 
	{
		cout << "succes " << buffer << endl; 
		close(fd);
	}
}
