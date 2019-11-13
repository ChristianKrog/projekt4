#include "controlunit.h"
//#include "moist.h"
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
	}

	return 0;
}