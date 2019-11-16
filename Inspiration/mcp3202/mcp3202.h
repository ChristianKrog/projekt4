
#include <iostream>

using namespace std;

class MCP3202
{
public:
	MCP3202(int = 0);
	void initADC();
	int readADC();

private: 
	int channel_;
	
};