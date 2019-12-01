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
	int temp;
	unsigned char address = 0x4C;
	temp = Controlunit::readI2C(address);
	return temp;
}

void Temperature::regulateTemperature(unsigned char slaveAddress, int ref)  //Recives the desired/reference temperature and sends the correct duty cycle for the heat PWM on I2C slaveAddress
{
	float a0Temp = 99.24;
	float a1Temp = -98.76;
	float b1Temp = 1;

	int temp = getTemp();				//Gets temperature and saves it in temp
	cout << temp << endl;
	errorTemp = ref - temp;				//Error is set to the difference between the reference and the current temperature

	if(errorTemp < 0)					//If error is negative the fan will turn on for a second.
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
		Controlunit::sendI2C(slaveAddress, 1, 100);					//Sends dutycycle 100% to PWM1
	}
	else if (controlsignalTemp <= 0)					//Sets the duty cycle at 0% if current controlsignal is equal to or lower than 0
	{
		Controlunit::sendI2C(slaveAddress, 1, 0);						//Sends dutycycle 0% to PWM1
	}
	else
	{
		Controlunit::sendI2C(slaveAddress, 1, (int)controlsignalTemp/10);   //Sends controlsignal divided by 10 to PWM1			
	}
}

