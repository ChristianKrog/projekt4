#pragma once
#ifndef MOIST_H
#define MOIST_H
#include "controlunit.h"
class Moist: public Controlunit
{
public: 
	Moist();
	~Moist();
	int getMoist(int ); 
	void printMoist();
	void setMoist(int ); //not used yet
	void startPump();
	void stopPump();
	void regulateMoisture(int, int, int);


private: 

	bool rainwaterLevel();
	void selectWaterSupply();
	void openValve(int );
	void closeValve(int );
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