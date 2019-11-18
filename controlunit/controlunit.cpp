#include "controlunit.h"
#include <cstring>

Controlunit::Controlunit()
{

	
	//////////////////UART////////////////
	//this->initUART();
}

Controlunit::~Controlunit()
{
	this->killSPI();

	//////////////////UART//////////////////
	//this->killUART();
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

void Controlunit::initI2C()
{
		
}
void Controlunit::sendI2C(int timer, int dutycycle)
{
	char str1[1] = {(char)timer};
	char str2[3] = {(char)dutycycle};
	char str3[1] = {','};
	strcat(str1, str3);
	strcat(str1, str2);
	char buffer[8] = {*str1};
	int fd, fdVal;


	fd = open("/dev/i2c-1", O_RDWR);

	if (fd == -1) {
		cout << "Error fd i2c: " << strerror(errno) << endl;
	}

	ioctl(fd, I2C_SLAVE_FORCE, 0x32);
	fdVal = write(fd, buffer, strlen(buffer));

	if (fdVal == -1) 
	{
		cout << "Error write: " << strerror(errno) << endl;
		close(fd);
	}
	else 
	{
		cout << "succes" << endl; 
		close(fd);
	}
}


/*
int Controlunit::initUART()
{
	port(io, "/dev/ttyS0");
	int baudrate = 9600

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
