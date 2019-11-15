#pragma once
#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "controlunit.h"

class Temperature: public Controlunit
{
public: 
	Temperature();
	~Temperature();
	float getTemp();
	void setTemp(int );
	void startFan();
	void stopFan();
	void startHeater();
	void stopHeater();
private: 
	int temp_;
	uint8_t gpioRead();
};
#endif
/*
//#include <wiringPi.h> //might be useless 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
using namespace std;

class Temperature
{
public: 
	Temperature();
	~Temperature();
	float getTemp();
	void setTemp(int );
	void startFan();
	void stopFan();
	void startHeater();
	void stopHeater();
private: 
	int temp_;
	uint8_t gpioRead();
		
}; */
