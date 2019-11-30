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

private: 
	int getMoist(int sensorID); 
	bool rainwaterLevel();
	void selectWaterSupply();
	void openValve(int valveID);
	void closeValve(int valveID);
	int errorMoist0;
	int errorPriorMoist0;
	int controlsignalMoist0;
	int controlsignalPriorMoist0; 
	int errorMoist1;
	int errorPriorMoist1;
	int controlsignalMoist1;
	int controlsignalPriorMoist1; 
};
#endif 