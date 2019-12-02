#include "controlunit.h"
#include "temperature.h"
#include "moist.h"

#define PSOC_I2C_ADDRESS 0x08
#define TEMP_REF 30
#define MOIST0_REF 10
#define MOIST1_REF 10
#define DELAY 1
#define MOIST_DELAY_US 100000 

int main()
{	
	//int moist0 = 0, moist1 = 0;

	Moist m;
	Temperature t;
	
	m.startPump(); //Start Pump so we are ready to deliver some water! 
	sleep(DELAY);
	m.stopPump();


	while (1)
	{
		/*
		moist0 = m.getMoist(0);
		moist1 = m.getMoist(1);

		cout << moist0  << " | " << moist1 << endl; 

		sleep(DELAY);
		*/

		/*
		t.regulateTemperature(PSOC_I2C_ADDRESS, TEMP_REF);
		sleep(DELAY);

		moist0 = m.getMoist(0);
		moist1 = m.getMoist(1);

		if(moist0 < MOIST0_REF)
		{
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 2 , 100);
			usleep(MOIST_DELAY_US);
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 2 , 0);
		}
		if(moist1 < MOIST1_REF)
		{
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 3 , 100);
			usleep(MOIST_DELAY_US);
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 3 , 0);
		}
		*/
		/*
		m.regulateMoisture(PSOC_I2C_ADRESS, 0, MOIST0_REF);
		m.regulateMoisture(PSOC_I2C_ADRESS, 1, MOIST1_REF);
		temp = t.getTemp();
		cout << temp << endl;
		t.Controlunit::sendI2C(1,10);
		*/
	}
	return 0;
}