#include "controlunit.h"
#include "temperature.h"
#include "moist.h"

#define PSOC_I2C_ADDRESS 0x08
#define TEMP_REF 30
#define MOIST0_REF 30
#define MOIST1_REF 30
#define DELAY 1
#define MOIST_DELAY_US 100000 

int main()
{	
	Moist m;
	Temperature t;

	int moist0 = 0, moist1 = 0;

	m.startPump();

	while (1)
	{
		t.regulateTemperature(PSOC_I2C_ADDRESS, TEMP_REF);
		
		moist0 = m.getMoist(0);
		moist1 = m.getMoist(1);

		cout << "S0: " << moist0 << " | S1: " << moist1 << endl;

		

		if(moist0 < MOIST0_REF)
		{	
			m.selectWaterSupply();
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 2 , 100);
			usleep(MOIST_DELAY_US);
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 2 , 0);
		}
		if(moist1 < MOIST1_REF)
		{
			m.selectWaterSupply();
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 3 , 100);
			usleep(MOIST_DELAY_US);
			m.Controlunit::sendI2C(PSOC_I2C_ADDRESS, 3 , 0);
		}

		sleep(DELAY);
	}
	return 0;
}


	//
	/*
	m.startPump(); //Start Pump so we are ready to deliver some water! 
	sleep(DELAY);
	m.stopPump();
	*/

		/*
		cout << "Temperatur: "<< t.readI2C(0x48) << endl;
		sleep(1);
		*/

		/*
		moist0 = m.getMoist(0);
		moist1 = m.getMoist(1);

		cout << "AIN0: " << moist0  << " | AIN1: " << moist1 << endl; 

		sleep(DELAY);
		*/

		/*
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