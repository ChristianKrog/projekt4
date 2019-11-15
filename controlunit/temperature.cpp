#include "temperature.h"




/*Temperature::Temperature()
{
	
	
}

Temperature::~Temperature()
{
	
}

float Temperature::getTemp()
{	
	#define MAX_TIMINGS 85
	uint8_t laststate = 1;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	int data[5] = { 0, 0, 0, 0, 0 };
	
	
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	//int fd1, fd1Dat;
	int fd2, fd2Data, fd3, fd3Data, fd2Write, fd2WriteData;
	//char exportBuffer[3] = "17";
	char directionInBuffer[4] = "in", directionOutBuffer[4] = "out", BUF[8];
	
	
		fd1 = open("/sys/class/gpio/export", O_WRONLY);
		fd1Data = write(fd1, exportBuffer, strlen(exportBuffer));
		if (fd1Data == -1)
		{
			cout << "Error on writing to export. " << strerror(errno) << endl;
		}
		else
		{
		cout << "Bytes written to export : " << fd1Data << endl;
		close(fd1);
		}
    
	BUF[0] = 48;
	//Writing to direction. Setting up direction for port to OUTPUT. 
	fd2 = open("/sys/class/gpio/gpio17/direction", O_WRONLY);
	fd2Data = write(fd2, directionOutBuffer, strlen(directionOutBuffer));

	if (fd2Data == -1)
	{
		cout << "Error on writing to direction. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Bytes written to direction : " << fd2Data << endl;
		close(fd2);
	}

	//Setting port high
	fd2Write = open("/sys/class/gpio/gpio17/value", O_WRONLY);
	fd2WriteData = write(fd2Write, BUF, 1);

	if (fd2WriteData == -1)
	{
		cout << "Error on writing to value. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Bytes written to value : " << fd2WriteData << endl;
		usleep(500000);
		close(fd2Write);
	}

	//Setting port low
	fd2Write = open("/sys/class/gpio/gpio17/value", O_WRONLY);
	fd2WriteData = write(fd2Write, BUF, 0);

	if (fd2WriteData == -1)
	{
		cout << "Error on writing to value. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Bytes written to value : " << fd2WriteData << endl;
		usleep(20000);
		close(fd2Write);
	}

	//Writing to direction. Setting up direction for port to INPUT. 
	fd3 = open("/sys/class/gpio/gpio17/direction", O_WRONLY);
	fd3Data = write(fd3, directionInBuffer, strlen(directionInBuffer));

	if (fd3Data == -1)
	{
		cout << "Error on writing to direction. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Bytes written to direction : " << fd3Data << endl;
		close(fd3);
	}
  
	//detect change and read data 
	for ( i = 0; i < MAX_TIMINGS; i++ )
	{
		counter = 0;
		while ( this->gpioRead() == laststate )
		{
			counter++;
			usleep( 2 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = this->gpioRead();
 
		if ( counter == 255 )
			break;
		
			
 
		//ignore first 3 transitions 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			//shove each bit into the storage bytes 
			data[j / 8] <<= 1;
			if ( counter > 16 )
				data[j / 8] |= 1;
			j++;
		}
	}
 
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
        float t, h;
        h = (float)data[0] * 256 + (float)data[1];
        h /= 10;
        t = (float)(data[2] & 0x7F)* 256 + (float)data[3];
        t /= 10.0;
        if ((data[2] & 0x80) != 0)  t *= -1;


    printf("Humidity = %.2f %% Temperature = %.2f *C \n", h, t );
    return t;
  }
  else
  {
    printf("Data not good, skip\n");
    return 0;
  }

}

/*
uint8_t Temperature::gpioRead()
{
	char buf[8];
	int fd, fdRead;

	for(int i = 0; i < 8; i++)
	{
		buf[i] = 0;
	}

	fd = open("/sys/class/gpio/gpio17/value", O_RDONLY);
	fdRead = read(fd, buf, 1);

if(fdRead == -1)
{
	printf("Error: %s\n", strerror(errno));
	close(fd);
}
else
{
	close(fd);
}

	return((uint8_t)atoi(buf));
} */
