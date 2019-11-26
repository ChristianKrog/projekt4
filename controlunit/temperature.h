#pragma once
#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "controlunit.h"
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
using namespace std;

class Temperature: public Controlunit
{
public: 
	Temperature();
	~Temperature();
	int getTemp();
	void setTemp(int );
	void startFan();
	void stopFan();

private: 


};
#endif
