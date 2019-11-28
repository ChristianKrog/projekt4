#pragma once
#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include "controlunit.h"

class Temperature: public Controlunit
{
public: 
	Temperature();
	~Temperature();
	void setTemp(int );
	void startFan();
	void stopFan();
	void regulateTemperature(int, int);

private: 
	int getTemp();
	int errorTemp;
	int errorPriorTemp;
	int controlsignalTemp;
	int controlsignalPriorTemp;
};
#endif
