#pragma once
#include <iostream>
using namespace std;

class Moist
{
public: 
	int getMoist(); 
	void setMoist(); 
	void startPump();
	void stopPump();
	void openValve(int );
	void closeValve(int ); 
	bool rainwaterLevel();
	void selectWaterSupply();
private: 
}