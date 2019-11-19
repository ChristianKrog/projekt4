#pragma once

#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H
class Moist;
class Temperature;

//#include "database.h"
////////////UART////////////////////// 
/*
#include <boost/asio.hpp> 
#include <boost/asio/serial_port.hpp> 
#include <boost/asio/serial_port_base.hpp>
*/
//////////////////////////////       
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
	void sendI2C(unsigned char, unsigned char);


protected: 
	unsigned char bitsPerWord_;
	unsigned int speed_;
	int spifd_;
	int initSPI();
	int killSPI();
	void initI2C();


	/////////////////////UART//////////////////////////////
	/*
	int* pathPoint;
	asio::io_service    				io;
	asio::serial_port   				port;
	*/
	
private:
	unsigned char mode_;


	/////////////////////UART//////////////////////////////
	/*
	int initUART();
	int killUART();
	*/
};
#endif