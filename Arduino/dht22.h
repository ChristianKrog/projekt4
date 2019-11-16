#pragma once
#ifndef DHT22_H
#define DHT22_H
#include "arduinoDAG.h"
#include <stdio.h>
#include "DHT.h"
class DHT22: public arduinoDAG
{
public:
	void sendTemp();
	float getTemp();
private:
	void sendCharUART(char );
	float temp_;
};
#endif