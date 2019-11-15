#include "moist.h"
#include <cstring>

Moist::Moist()
{
	#define NUM_OF_GPIOS 5 
	int fd, fdVal;
	char directionBuffer[] = "out";
	char exportBuffer22[] = "22";
	char exportBuffer23[] = "23";
	char exportBuffer24[] = "24";
	char exportBuffer25[] = "25";
	char exportBuffer27[] = "27";
	char pathDir22[] = "/sys/class/gpio/gpio22/direction";
	char pathDir23[] = "/sys/class/gpio/gpio23/direction";
	char pathDir24[] = "/sys/class/gpio/gpio24/direction";
	char pathDir25[] = "/sys/class/gpio/gpio25/direction";
	char pathDir27[] = "/sys/class/gpio/gpio27/direction"; 
	char *pathDir, *exportBuffer;

	for (int i = 0; i < NUM_OF_GPIOS; i++)
	{
		if (i == 0) //valve 0
		{
			pathDir = pathDir22;
			exportBuffer = exportBuffer22;
		}
		if (i == 1)//valve 1
		{
			pathDir = pathDir23;
			exportBuffer = exportBuffer23;
		}
		if (i == 2)//valve 2
		{
			pathDir = pathDir24;
			exportBuffer = exportBuffer24;
		}
		if (i == 3)//valve 3
		{
			pathDir = pathDir25;
			exportBuffer = exportBuffer25;
		}
		if (i == 4)//Pump
		{
			pathDir = pathDir27;
			exportBuffer = exportBuffer27;
		}	

		fd = open("/sys/class/gpio/export", O_WRONLY);
		fdVal = write(fd, exportBuffer, strlen(exportBuffer));
		if (fdVal == -1)
		{
			cout << "Error on writing to export. GPIO" << exportBuffer << ". " << strerror(errno) << endl;
		}
		else
		{
			cout << "Bytes written to export : " << fdVal << endl;
			close(fd);
		}

		//Writing to direction. Setting up direction for port to OUTPUT. 
		fd = open(pathDir, O_WRONLY);
		fdVal = write(fd2, directionBuffer, strlen(directionBuffer));
		if (fdVal == -1)
		{
			cout << "Error on writing to direction. " << strerror(errno) << endl;
		}
		else
		{
			cout << "Bytes written to direction : " << fdVal << endl;
			close(fd);
		}
	}
}

Moist::~Moist()
{
#define NUM_OF_GPIOS 5 
	int fd, fdVal;
	char directionBuffer[] = "out";

	for (int i = 0; i < NUM_OF_GPIOS; i++)
	{
		if (i == 0) //valve 0
		{
			char exportBuffer[] = "22";
		}

		if (i == 1)//valve 1
		{
			char exportBuffer[] = "23";
		}

		if (i == 2)//valve 2
		{
			char exportBuffer[] = "24";
		}

		if (i == 3)//valve 3
		{
			char exportBuffer[] = "25";
		}

		if (i == 4)//Pump
		{
			char exportBuffer[] = "27";
		}

		fd = open("/sys/class/gpio/unexport", O_WRONLY);
		fdVal = write(fd1, exportBuffer, strlen(exportBuffer));
		if (fdVal == -1)
		{
			cout << "Error on writing to unexport. " << exportBuffer << ". " << strerror(errno) << endl;
		}
		else
		{
			cout << "Bytes written to export : " << fdVal << endl;
			close(fd1);
		}
	}
}

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

	retVal = ioctl(this->spifd_, SPI_IOC_MESSAGE(length), &spi);

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

void Moist::startPump()
{
	int fd, fdVal;
	char BUF[]; //Maybe this should have a value!? 
	char pathVal[] = "/sys/class/gpio/gpio27/value";
	//Setting port high
	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd2Write, BUF, 1);

	if (fdVal == -1)
	{
		cout << "Error on writing to pump. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Pump started" << endl;
		close(fd);
	}
}

void Moist::stopPump()
{
	int fd, fdVal;
	char BUF[]; //Maybe this should have a value!? 
	char pathVal[] = "/sys/class/gpio/gpio27/value";
	//Setting port low
	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd2Write, BUF, 0);

	if (fdVal == -1)
	{
		cout << "Error on writing to pump. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Pump stopped" << endl;
		close(fd);
	}
}

void Moist::openValve(int valveID)
{
	int fd, fdVal; 
	char BUF[]; //Maybe this should have a value!? 
	if (valveID == 0)
	{
		char pathVal[] = "/sys/class/gpio/gpio22/value" ;
	}
	else if (valveID == 1)
	{
		char pathVal[] = "/sys/class/gpio/gpio23/value";
	}
	else if (valveID == 2)
	{
		char pathVal[] = "/sys/class/gpio/gpio24/value";
	}
	else if (valveID == 3)
	{
		char pathVal[] = "/sys/class/gpio/gpio25/value";
	}
	else
	{
		cout << "ValveID not registrated. Has to be between 1 and 4."
	}

	//Setting port high
	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd2Write, BUF, 1);

	if (fdVal == -1)
	{
		cout << "Error on writing to valve" << valveID <<". " << strerror(errno) << endl;
	}
	else
	{
		cout << "Valve" << valveID << " open" << endl;
		close(fd);
	}
}

void Moist::closeValve(int valveID)
{
	int fd, fdVal;
	char BUF[]; //Maybe this should have a value!? 
	if (valveID == 0)
	{
		char pathVal[] = "/sys/class/gpio/gpio22/value";
	}
	else if (valveID == 1)
	{
		char pathVal[] = "/sys/class/gpio/gpio23/value";
	}
	else if (valveID == 2)
	{
		char pathVal[] = "/sys/class/gpio/gpio24/value";
	}
	else if (valveID == 3)
	{
		char pathVal[] = "/sys/class/gpio/gpio25/value";
	}
	else
	{
		cout << "ValveID not registrated. Has to be between 1 and 4."
	}

	//Setting port Low
	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd2Write, BUF, 0);

	if (fdVal == -1)
	{
		cout << "Error on writing to valve" << valveID << ". " << strerror(errno) << endl
	}
	else
	{
		cout << "Valve" << valveID << " closed" << endl;
		close(fd);
	}
}
