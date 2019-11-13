#include "controlunit.h"

int main()
{
	Controlunit c; 

	while (1)
	{
		c.printADC();

		usleep(100);
	}

	return 0;
}