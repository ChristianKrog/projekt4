#pragma once



#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H
class Moist;
#include "temperature.h"
//#include "database.h"
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

class Controlunit
{
public:
	Controlunit();
	~Controlunit();
	//int readADC(int );
	//void printADC(); 

protected: 
	unsigned char bitsPerWord_;
	unsigned int speed_;
	int spifd_;
	
private:
	unsigned char mode_;
	int channel_;
	int initSPI();
	int killSPI();
};
#endif