#include "controlunit.h"
#include "temperature.h"
#include "moist.h"
#include "arduinoIF.h"

Moist m;
Temperature t;
seriel_C
int temp;
	
int main()
{
	////////////////UART//////////////////
	UART::seriel_com port(9600, 1, 0);


	while (1)
	{
		
		//m.printMoist();
		temp = t.getTemp();
		cout << temp << endl;
<<<<<<< Updated upstream
		m.printMoist();
=======
		
		////////////////UART//////////////////
		char tempChar[] = temp;
		port.send_string(tempChar);
		
>>>>>>> Stashed changes

		sleep(2);
	}
	return 0;
}