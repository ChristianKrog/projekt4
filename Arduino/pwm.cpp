#include "pwm.h"

PWM::PWM()
{
	this->initPWM();
}

PWM::~PWM()
{
}

void PWM::setPWMSignal(int timer, float dutyCycle)
{
    int OCRn = 0;
    int TOP = 1023; //Phase Correct 10-bit (TOP = 1023)
		
	if(dutyCycle <= 100 && dutyCycle >= 0 )		//Validating if dutycycle is equal to or between 0 - 100%
	{
		OCRn = -(TOP*((dutyCycle/100)-1));		//Calculating the trigger point for when signal should go high
	}
	
	if (timer == 1 | timer == 3 | timer == 4)	//Validating if timer is a 16-bit timer
	{
		if (timer == 1)							//(PIN 11) and 12
		{
			TCCR1A = 0b11000011;				//PWM, Phase Correct 10-bit (TOP = 1023), Set OCnA/OCnB/OCnC on compare match when up-counting
			TCCR1B = 0b00000101;				//Prescaler 1024
			OCR1A = OCRn;						//OCRn is set to generate the desired duty cycle
		}
		if (timer == 3)							//(PIN 5) and 3 and 2
		{
			TCCR3A = 0b11000011;
			TCCR3B = 0b00000101;
			OCR3A = OCRn;
		}
		if (timer == 4)							//(PIN 6) and 7 and 8
		{
			TCCR4A = 0b11000011;
			TCCR4B = 0b00000101;
			OCR4A = OCRn;
		}
	}
		else
		{
			printf("Invalid timer, use 1, 3 or 4\n");
			exit(EXIT_FAILURE);
		}
	}

}

void PWM::initPWM()
{
	//Timer 1 (PIN 11)
	PORTB = 0xFF;								//Sets pins as output
	DDRB = 0xFF;								//Sets pins as output
	//Timer 3 (PIN 5)
	PORTE = 0xFF;								//Sets pins as output
	DDRE = 0xFF;								//Sets pins as output
	//Timer 4 (PIN 6)
	PORTH = 0xFF;								//Sets pins as output
	DDRH = 0xFF;								//Sets pins as output
}
