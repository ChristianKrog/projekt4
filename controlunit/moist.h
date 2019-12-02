#pragma once
#ifndef MOIST_H
#define MOIST_H
#include "controlunit.h"

class Moist: public Controlunit
{
public: 
	Moist();
	~Moist();
	void startPump();
	void stopPump();
	void regulateMoisture(unsigned char slaveAddress, int sensorID, int ref);
	int getMoist(int sensorID);
	void selectWaterSupply();

private: 
	bool rainwaterLevel();
	void openValve(int valveID);
	void closeValve(int valveID);
	float errorMoist0;
	float errorPriorMoist0;
	float controlsignalMoist0;
	float controlsignalPriorMoist0; 
	float errorMoist1;
	float errorPriorMoist1;
	float controlsignalMoist1;
	float controlsignalPriorMoist1; 
};
#endif 