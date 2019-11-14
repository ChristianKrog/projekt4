#include "temperature.h"

Temperature::Temperature()
{
	pinDHT_ = 3; //GPIO 22
	int fd1, fd1Data, fd2, fd2Data, fd3, fd3Data, fd2Write, fd2WriteData;
	int exportBuffer[3] = "22", directionInBuffer[4] = "in", directionOutBuffer[4] = "out", BUF[3];
	int 
	
	//Writing to export. Setting up port
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

	//Writing to direction. Setting up direction for port to OUTPUT. 
	fd2 = open("/sys/class/gpio/gpio20/direction", O_WRONLY);
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
	fd2Write = open("/sys/class/gpio/gpio20/value", O_WRONLY);
	fd2WriteData = write(fd2Write, BUF, 1);

	if (fd2WriteData == -1)
	{
		cout << "Error on writing to value. " << strerror(errno) << endl;
	}
	else
	{
		cout << "Bytes written to direction : " << fd2WriteData << endl;
		usleep(1);
		close(fd2Write);
	}

	//Writing to direction. Setting up direction for port to INPUT. 
	fd3 = open("/sys/class/gpio/gpio20/direction", O_WRONLY);
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


	/*
	wiringPiSetup();
	//pull pin down for 18 milliseconds s
	pinMode(pinDHT_, OUTPUT);
	digitalWrite(pinDHT_, LOW);
	usleep(18);

	//prepare to read the pin
	pinMode(pinDHT_, INPUT);
	*/
}

Temperature::~Temperature()
{
	
}

int Temperature::getTemp()
{	
	int fd, fdData, i, data[5] = { 0, 0, 0, 0, 0 };;
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
	uint8_t laststate = HIGH;

	//Read data: 
	unsigned short val = 0x00;
	unsigned short signal_length = 0;
	unsigned short val_counter = 0;
	unsigned short loop_counter = 0;

	while (1)
	{
		// Count only HIGH signal
		while (this->gpioRead == 1)
		{
			signal_length++;

			// When sending data ends, high signal occur infinite.
			// So we have to end this infinite loop.
			if (signal_length >= 200)
			{
				return -1;
			}

			usleep(1);
		}

		// If signal is HIGH
		if (signal_length > 0)
		{
			loop_counter++;	// HIGH signal counting

			// The DHT22 sends a lot of unstable signals.
			// So extended the counting range.
			if (signal_length < 10)
			{
				// Unstable signal
				val <<= 1;		// 0 bit. Just shift left
			}

			else if (signal_length < 30)
			{
				// 26~28us means 0 bit
				val <<= 1;		// 0 bit. Just shift left
			}

			else if (signal_length < 85)
			{
				// 70us means 1 bit
				// Shift left and input 0x01 using OR operator
				val <<= 1;
				val |= 1;
			}

			else
			{
				// Unstable signal
				return -1;
			}

			signal_length = 0;	// Initialize signal length for next signal
			val_counter++;		// Count for 8 bit data
		}

		// The first and second signal is DHT22's start signal.
		// So ignore these data.
		if (loop_counter < 3)
		{
			val = 0x00;
			val_counter = 0;
		}

		// If 8 bit data input complete
		if (val_counter >= 8)
		{
			// 8 bit data input to the data array
			data[(loop_counter / 8) - 1] = val;

			val = 0x00;
			val_counter = 0;
		}
	}

	/*
	int MAX_TIMINGS = 85;
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	int data[5] = { 0, 0, 0, 0, 0 };
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	//detect change and read data
	for (i = 0; i < MAX_TIMINGS; i++)
	{
		counter = 0;
		while (digitalRead(pinDHT_) == laststate)
		{
			counter++;
			usleep(1);
			if (counter == 255)
			{
				break;
			}
		}
		laststate = digitalRead(pinDHT_);

		if (counter == 255)
			break;

		//ignore first 3 transitions 
		if ((i >= 4) && (i % 2 == 0))
		{
			//shove each bit into the storage bytes 
			data[j / 8] <<= 1;
			if (counter > 16)
				data[j / 8] |= 1;
			j++;
		}
	}

	//Humidity
	float h = (float)((data[0] << 8) + data[1]) / 10;
		if ( h > 100 )
		{
			h = data[0];	
		}
	
	//Temperature
	float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
	
	if ( data[2] & 0x80 )
	{
		c = -c;
	}	
	
	return c;
	*/
}

int Temperature::gpioRead()
{
#define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pinDHT_);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-1);
	}

	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Failed to read value!\n");
		return(-1);
	}

	close(fd);

	return(atoi(value_str));
}
