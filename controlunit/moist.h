#pragma once
#ifndef MOIST_H
#define MOIST_H
#include "controlunit.h"
//Check which libraries are necesarry
/*
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;
*/



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
	void openValve(int );
	void closeValve(int ); 
	bool rainwaterLevel();
	void selectWaterSupply();
private: 
	int moist_;
	int sensorID_; //not used yet 
	int valveID_; 
	bool waterLevel;
};
#endif 