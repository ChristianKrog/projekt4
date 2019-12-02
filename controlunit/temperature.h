#pragma once
#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "controlunit.h"

class Temperature: public Controlunit
{
public: 
	Temperature();
	~Temperature();
	void regulateTemperature(unsigned char slaveAddress, int ref);

private: 
	int getTemp();
	void startFan();
	void stopFan();
	float errorTemp;
	float errorPriorTemp;
	float controlsignalTemp;
	float controlsignalPriorTemp;
};
#endif
