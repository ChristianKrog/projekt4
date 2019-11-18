#include "temperature.h"

#include <cstring>


Temperature::Temperature()
{
}

Temperature::~Temperature()
{
}

float Temperature::getTemp()
{
	char buffer[8];
	float temp; 
	int fd, fdVal;


	fd = open("/dev/i2c-1", O_RDWR);

	if (fd == -1) {
		printf("File directory error: %s\n", strerror(errno));
	}

	ioctl(fd, 0x0703, 0x4C); 
	fdVal = read(fd, buffer, 2);

	if (fdVal == -1) {
		printf("Read Error: %s\n", strerror(errno));
		sleep(1);
		close(fd);
	}
	else 
	{
		buffer[fdVal] = 0;
		temp = buffer[0];
		close(fd);
	}
	
	return temp;
}

