#pragma once

#ifndef PWM_H
#define PWM_H
class PWM
{
public:
	PWM();
	~PWM();
	void setPWMSignal(int timer, float dutyCycle);

private:
	void initPWM();
	
};
#endif