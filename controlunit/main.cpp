#include "controlunit.h"
#include "moist.h"
int main()
{
	Moist m; 

	while (1)
	{
		m.printMoist();

		usleep(100);
	}

	return 0;
}