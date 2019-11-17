#include "controlunit.h"
#include "temperature.h"
#include "moist.h"


//Moist m;
Temperature t;

int temp;
	
int main()
{
	////////////////UART//////////////////
	//UART::seriel_com port(9600, 1, 0);


	while (1)
	{
		
		//m.printMoist();
		
		temp = t.getTemp();
		cout << temp << endl;
		t.sendI2C(1, 10);

		
		////////////////UART//////////////////
		//string duty = "10";
		//port.send_string(duty);
		
		sleep(1);
	}
	return 0;
}