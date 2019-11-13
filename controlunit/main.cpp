#include "controlunit.h"

int main()
{
	Controlunit c; 
	int ch0, ch1; 
	while (1)
	{
		c.printADC();

		usleep(100);
	}

	return 0;
}