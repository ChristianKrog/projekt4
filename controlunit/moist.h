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
	void setMoist(int ); 
	void startPump();
	void stopPump();


private: 
	int moist_;   //not used yet
	int sensorID_; //not used yet 
	int valveID_; //not used yet
	bool waterLevel_; //not used yet 
	void openValve(int );
	void closeValve(int ); 
	bool rainwaterLevel();
	void selectWaterSupply();
};
#endif 