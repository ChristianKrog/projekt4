#include "controlunit.h"
#include "temperature.h"
#include "moist.h"

	//Moist m;
Temperature t;
int temp;
	
int main()
{
	while (1)
	{
		//m.printMoist();
		temp = t.getTemp();
		cout << temp << endl;

		sleep(2);
	}
	return 0;
}