#include "controlunit.h"
#include "temperature.h"
#include "moist.h"

#define PSOC_I2C_ADRESS 0x08
#define TEMP_REF 30
#define MOIST0_REF 50
#define MOIST1_REF 50
#define DELAY 1


int main()
{
	//Moist m;
	Temperature t;
	//m.startPump(); //Start Pump so we are ready to deliver some water! 

	while (1)
	{
		t.regulateTemperature(PSOC_I2C_ADRESS, TEMP_REF);
		//m.regulateMoisture(PSOC_I2C_ADRESS, 0, MOIST0_REF);
		//m.regulateMoisture(PSOC_I2C_ADRESS, 1, MOIST1_REF);
		sleep(DELAY);
		
		//temp = t.getTemp();
		//cout << temp << endl;
		//t.Controlunit::sendI2C(1,10);
	}
	return 0;
}