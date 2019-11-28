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


void Temperature::stopFan()
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
	unsigned char address = 0x4C;

	fd = open("/dev/i2c-1", O_RDWR);

	if (fd == -1) 
	{
		printf("File directory error: %s\n", strerror(errno));
	}

	ioctl(fd, 0x0703, address); 
	fdVal = read(fd, BUF, 2);

	if (fdVal == -1) 
	{
		printf("Read Error: %s\n", strerror(errno));
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

void Temperature::regulateTemperature(int choosePWM, int ref)  //Recives the current temperature reading togehter with the desired/reference temperature and returns the correct duty cycle for the selected PWM
{
	float a0Temp = 99.24;
	float a1Temp = -98.76;
	float b1Temp = 1;

	int temp = getTemp();

	errorTemp = ref - temp;				//Error is set to the difference between the reference and the current temperature

	if(errorTemp < 0)
	{
		startFan();
		sleep(1);
		stopFan();
	}

	controlsignalTemp =  (int)(a0Temp * errorTemp + (a1Temp) * errorPriorTemp + controlsignalPriorTemp * b1Temp);	//Current controlsignal calcuation, typecasting is used to round floats correctly
	
	errorPriorTemp = errorTemp;						//Setting the current temperature error as the prior temperature error
	controlsignalPriorTemp = controlsignalTemp;		//Setting the current controlsignal as the prior controlsignal
	
	if (controlsignalTemp >= 1000)						//Sets the duty cycle at 100% if current controlsignal is equal to or greater than 1000
	{
		Controlunit::sendI2C(choosePWM, 100);
	}
	else if (controlsignalTemp <= 0)					//Sets the duty cycle at 0% if current controlsignal is equal to or lower than 0
	{
		Controlunit::sendI2C(choosePWM, 0);
	}
	else
	{
		Controlunit::sendI2C(choosePWM, (int)controlsignalTemp/10);   //Retuns the current controlsignal, divided by 10 to scale the duty cycle appropriately				
	}
}

