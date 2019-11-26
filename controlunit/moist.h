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



private: 

	bool rainwaterLevel();
	void selectWaterSupply();
	void openValve(int );
	void closeValve(int ); 
};
#endif 