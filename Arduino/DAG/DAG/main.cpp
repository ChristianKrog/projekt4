#include "arduinoDAG.h"
#include "dht22.h"
#include "DHT.h"
#include "pwm.h"

#define F_CPU 16000000


int main()
{
	//PWM pwm;
	//pwm.setPWMSignal(1, 20);
	//DHT22 dht; 
	DHT dht;
	dht.begin();
	
	float t; 
	t = dht.readTemperature();
	
	
	return 0;
}