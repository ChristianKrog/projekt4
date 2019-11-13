#pragma once
#include <iostream>
using namespace std;

class Moist
{
public: 
	int getMoist(int ); 
	void setMoist(int ); 
	void startPump();
	void stopPump();
	void openValve(int );
	void closeValve(int ); 
	bool rainwaterLevel();
	void selectWaterSupply();
private: 
	int moist_;
	int sensorID_; 
	int valveID_; 
	bool waterLevel
}