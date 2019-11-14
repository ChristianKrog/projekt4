#include "controlunit.h"

int main()
{
	//Moist m; 
	Temperature t;
	int temp;

	while (1)
	{
		//m.printMoist();
		//usleep(100);
		temp = t.getTemp(); 
		cout << temp << endl;
		sleep(2);

	}

	return 0;
}