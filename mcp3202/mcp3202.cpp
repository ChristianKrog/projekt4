#include "mcp3202.h"
#include <bcm2835.h>
#include <iostream>

using namespace std;


MCP3202::MCP3202(int channel)
{
	channel_ = channel; 
}

void MCP3202::initADC()
{
	if (!bcm2835_init()) 
	{
		cout << "error (spi_init())" << endl;
	}
	if (!bcm2835_spi_begin()) 
	{
		cout << "error (spi_begin())" << endl;
	}
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW); 

}

int MCP3202::readADC()
{
	char tx[10] = { 0xF0, 0x00 }, rx[10] = { 0 };
	
	/*if(channel_ == 1)
	{
		tx[10] = { 0xF0, 0x00 };
	}
	else if (channel_ == 2)
	{
		tx[10] = { 0xD0, 0x00 };
	} */
		
	bcm2835_spi_transfernb(tx, rx, 2);

	int result = rx[1];
	result |= rx[0] << 8; 

	return result;
}
