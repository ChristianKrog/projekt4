#pragma once

#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H
class Moist;
class Temperature;     
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
	virtual ~Controlunit();
	void sendI2C(unsigned char address, unsigned char choosePWM, unsigned char dutycycle);
	int readI2C(unsigned char address);

protected: 
	int spifd_;
	int i2cfd_;
	void initSPI();
	void killSPI();
	
	

private:
	void initI2C();
	void killI2C();

};
#endif