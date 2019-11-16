#include "controlunit.h"
#include "moist.h"

	Moist m;
	
int main()
{
	
	while (1)
	{
		m.printMoist();
		sleep(1);

		/*
		temp = t.getTemp(); 
		cout << temp << endl;
		sleep(2);
		*/
	}

	return 0;
}