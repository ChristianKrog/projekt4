#pragma once
#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "controlunit.h"

class Temperature: public Controlunit
{
public: 
	Temperature();
	~Temperature();
	void startFan();
	void stopFan();
	void regulateTemperature(unsigned char slaveAddress, int ref);

private: 
	int getTemp();
	int errorTemp;
	int errorPriorTemp;
	int controlsignalTemp;
	int controlsignalPriorTemp;
};
#endif
