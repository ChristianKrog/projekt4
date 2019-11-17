#pragma once

#ifndef ARDUINODAG_H
#define ARDUINODAG_H
#include <avr/io.h>

class DHT22

class arduinoDAG
{
public:
	arduinoDAG();
	~arduinoDAG();
	
private:
	void initUART();
	unsigned long baudrate_;
	int databit_;
};
#endif