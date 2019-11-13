#pragma once
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
using namespace std;

class Temperature
{
public: 
	Temperature();
	~Temperature();
	int getTemp();
	void setTemp(int );
	void startFan();
	void stopFan();
	void startHeater();
	void stopHeater();
private: 
	int temp_;
	int pinDHT_ = 3
	void initDHT();
};