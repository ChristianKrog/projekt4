#ifndef PWMGENERATOR_H_
#define PWMGENERATOR_H_

class PWM
{
	public:
	PWM();
	~PWM();
	void setPWMSignal(int timer, float dutyCycle);

	private:
	void initPWM();
	void initUART();
	char readChar();
	
};
#endif