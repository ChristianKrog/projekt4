#pragma once
#include <iostream>
using namespace std;

class Temperature
{
public: 
	int getTemp();
	void setTemp(int );
	void startFan();
	void stopFan();
	void startHeater();
	void stopHeater();
private: 
	int temp_;
};