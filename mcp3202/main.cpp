#include "mcp3202.h"
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
	MCP3202 ch1(1), ch2(2);
	ch1.initADC();
	ch2.initADC();

	while (1)
	{
		cout << ch1.readADC() << " | " << ch2.readADC() << endl;
		usleep(100);
	}

    return 0;
}