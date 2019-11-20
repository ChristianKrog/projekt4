#include "moist.h"
#include <cstring>
#define NUM_OF_GPIOS 4 
int fd, fdVal;
char *exportBuffer, *pathDir, *pathVal;
char directionOutBuffer[] = "out";
char directionInBuffer[] = "in";
char BUF[8];
char exportBuffer22[] = "22"; //valve 0
char exportBuffer25[] = "25"; //valve 1
char exportBuffer27[] = "27"; //pump
char exportBuffer23[] = "23"; //Waterlevelsensor
char pathDir22[] = "/sys/class/gpio/gpio22/direction"; //valve 0
char pathDir25[] = "/sys/class/gpio/gpio25/direction"; //valve 1
char pathDir27[] = "/sys/class/gpio/gpio27/direction"; //pump 
char pathDir23[] = "/sys/class/gpio/gpio23/direction"; //Waterlevelsensor
char pathVal27[] = "/sys/class/gpio/gpio27/value"; //pump
char pathVal22[] = "/sys/class/gpio/gpio22/value"; //valve 0
char pathVal25[] = "/sys/class/gpio/gpio25/value"; //valve 1
char pathVal23[] = "/sys/class/gpio/gpio23/value"; //Waterlevelsensor

Moist::Moist()
{
	this -> initSPI();

	for (int i = 0; i < NUM_OF_GPIOS; i++)
	{
		if (i == 0) //valve 0
		{
			pathDir = pathDir22;
			exportBuffer = exportBuffer22;
		}
		if (i == 1)//valve 1
		{
			pathDir = pathDir25;
			exportBuffer = exportBuffer25;
		}

		if (i == 2)//Pump
		{
			pathDir = pathDir27;
			exportBuffer = exportBuffer27;
		}	
		if (i == 3) //Waterlevelsensor
		{
			exportBuffer = exportBuffer23;
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
		fdVal = write(fd, directionOutBuffer, strlen(directionOutBuffer));
		if (fdVal == -1)
		{
			cout << "Error on writing to direction. " << strerror(errno) << endl;
		}
		else
		{
			cout << "Bytes written to direction : " << fdVal << endl;
			close(fd);
		}

		////Writing to direction. Setting up direction for port to INPUT.(Waterlevelsensor) 
		fd = open(pathDir23, O_WRONLY);
		fdVal = write(fd, "in", 2);
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
	for (int i = 0; i < NUM_OF_GPIOS; i++)
	{
		if (i == 0) //valve 0
		{
			exportBuffer = exportBuffer22;
		}

		if (i == 1)//valve 1
		{
			exportBuffer = exportBuffer25;
		}

		if (i == 2)//Pump
		{
			exportBuffer = exportBuffer27;
		}
		if (i == 3)//Waterlevelsensor
		{
			exportBuffer = exportBuffer23;
		}

		fd = open("/sys/class/gpio/unexport", O_WRONLY);
		fdVal = write(fd, exportBuffer, strlen(exportBuffer));
		if (fdVal == -1)
		{
			cout << "Error on writing to unexport. " << exportBuffer << ". " << strerror(errno) << endl;
		}
		else
		{
			cout << "Bytes written to export : " << fdVal << endl;
			close(fd);
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

	moist_ = resultMoist;

	return resultMoist;
}

void Moist::printMoist()
{
	int ch0, ch1;
	ch0 = getMoist(0);
	ch1 = getMoist(1);

	cout << "CH0: " << ch0 << " | Ch1: " << ch1 << endl;
}

void Moist::startPump()
{
	//Setting port high
	fd = open(pathVal27, O_WRONLY);
	fdVal = write(fd, BUF, 1);

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
	//Setting port low
	fd = open(pathVal27, O_WRONLY);
	fdVal = write(fd, BUF, 0);

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
	if (valveID == 0)
	{
		pathVal = pathVal22;
	}
	else if (valveID == 1)
	{
		pathVal = pathVal25;
	}
	else
	{
		cout << "valveID not registrated. Has to be 0 or 1." << endl;
	}

	//Setting port high
	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd, BUF, 1);

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
	if (valveID == 0)
	{
		pathVal = pathVal22;
	}
	else if (valveID == 1)
	{
		pathVal = pathVal25;
	}
	else
	{
		cout << "valveID not registrated. Has to be between 0 or 1" << endl;
	}

	//Setting port Low
	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd, BUF, 0);

	if (fdVal == -1)
	{
		cout << "Error on writing to valve" << valveID << ". " << strerror(errno) << endl;
	}
	else
	{
		cout << "Valve" << valveID << " closed" << endl;
		close(fd);
	}
}

bool Moist::rainwaterLevel()
{
	fd = open(pathVal23, O_WRONLY);
	fdVal = read(fd, BUF, 1);

	if (fdVal == -1)
	{
		cout << "Error on reading from waterlevelsensor: " << strerror(errno) << endl;
	}
	else
	{
		close(fd);
	}

	if(BUF[0] == 1)
	{
		return true; 
	}
	else 
	{
		return false;
	}
}

void Moist::selectWaterSupply()
{	
	if(rainwaterLevel()) //opens valve0 and closes valve1 if rainwaterlevel == true;
	{
		openValve(0);
		closeValve(1);
	}
	else if(!rainwaterLevel()) //opens valve1 and closes valve0 if rainwaterlevel == false;
	{
		openValve(1);
		closeValve(0);
	}
	else 
	{
		cout << "Could not select watersupply" << endl; 
	}
}
