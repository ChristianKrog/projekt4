#include "temperature.h"

#include <cstring>


Temperature::Temperature()
{
	int fd, fdVal;
	char directionBuffer[] = "out";
	char exportBuffer[] = "24"; //Fan
	char pathDir[] = "/sys/class/gpio/gpio24/direction";

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
	fdVal = write(fd, directionBuffer, strlen(directionBuffer));
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

Temperature::~Temperature()
{
	int fd, fdVal; 
	char exportBuffer[] = "24";
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

void Temperature::startFan()
{
	int fd, fdVal; 
	int BUF[8];
	char pathVal[] = "/sys/class/gpio/gpio24/value";

	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd, BUF, 1);
	if (fdVal == -1)
	{
		cout << "Error on writing to fan. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Fan started" << endl;
		close(fd);
	}
}


void stopFan()
{
	int fd, fdVal; 
	int BUF[8];
	char pathVal[] = "/sys/class/gpio/gpio24/value";

	fd = open(pathVal, O_WRONLY);
	fdVal = write(fd, BUF, 0);
	if (fdVal == -1)
	{
		cout << "Error on writing to fan. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Fan stopped" << endl;
		close(fd);
	}
}

int Temperature::getTemp()
{
	char BUF[8];
	int temp; 
	int fd, fdVal;

	fd = open("/dev/i2c-1", O_RDWR);

	if (fd == -1) 
	{
		printf("File directory error: %s\n", strerror(errno));
	}

	ioctl(fd, 0x0703, 0x4C); 
	fdVal = read(fd, BUF, 2);

	if (fdVal == -1) 
	{
		printf("Read Error: %s\n", strerror(errno));
		sleep(1);
		close(fd);
	}
	else 
	{
		BUF[fdVal] = 0;
		temp = BUF[0];
		close(fd);
	}
	
	return temp;
}

