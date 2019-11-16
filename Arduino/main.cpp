#include "arduinoDAG.h"
#include "dht22.h"
#include "pwm.h"

#define F_CPU 16000000


int main()
{
	PWM pwm;
	pwm.setPWMSignal(1, 20);
	DHT22 dht; 
	
	return 0;
}