/***********************************************************************
 * mcp3008SpiTest.cpp. Sample program that tests the mcp3008Spi class.
 * an mcp3008Spi class object (a2d) is created. the a2d object is instantiated
 * using the overloaded constructor. which opens the spidev0.0 device with 
 * SPI_MODE_0 (MODE 0) (defined in linux/spi/spidev.h), speed = 1MHz &
 * bitsPerWord=8.
 * 
 * call the spiWriteRead function on the a2d object 20 times. Each time make sure
 * that conversion is configured for single ended conversion on CH0
 * i.e. transmit ->  byte1 = 0b00000001 (start bit)
 *                   byte2 = 0b1000000  (SGL/DIF = 1, D2=D1=D0=0)
 *                   byte3 = 0b00000000  (Don't care)
 *      receive  ->  byte1 = junk
 *                   byte2 = junk + b8 + b9
 *                   byte3 = b7 - b0
 *     
 * after conversion must merge data[1] and data[2] to get final result 
 * 
 * 
 * 
 * *********************************************************************/
#include "mcp3008Spi.h"
 
using namespace std;
 
int main(void)
{
    mcp3008Spi ch0("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    mcp3008Spi ch1("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    int ch0Val = 0; 
    int ch1Val = 0;
    unsigned char dataCH0[3];
    unsigned char dataCH1[3];
 
    while(1)
    {
        ///////////////////////////////////CHANNEL 0//////////////////////////////////////////////////
        dataCH0[0] = 1;  //  first byte transmitted -> start bit
        dataCH0[1] = 0b10100000; // Use channel 0. 
        dataCH0[2] = 0; // third byte transmitted....don't care
 
        ch0.spiWriteRead(dataCH0, sizeof(dataCH0) );
        
        /*ch0Val = 0;
        ch0Val = (dataCH0[0] & 0x07) << 9;
        ch0Val |= (dataCH0[1] & 0xFF) << 1;
        ch0Val |= (dataCH0[2] & 0x80) >> 7;
        ch0Val |= ch0Val & 0xFFF;*/
        ch0Val = 0;
        ch0Val = (dataCH0[1]<< 8) & 0b111100000000; //merge data[1] & data[2] to get result
        ch0Val |=  (dataCH0[2] & 0xff); 

        ///////////////////////////////////CHANNEL 1//////////////////////////////////////////////////
        dataCH1[0] = 1;  //  first byte transmitted -> start bit
        dataCH1[1] = 0b11100000; // Use channel 1. 
        dataCH1[2] = 0; // third byte transmitted....don't care

        ch1.spiWriteRead(dataCH1, sizeof(dataCH1) );

        /*ch1Val = 0;
        ch1Val = (dataCH1[0] & 0x07) << 9;
        ch1Val |= (dataCH1[1] & 0xFF) << 1;
        ch1Val |= (dataCH1[2] & 0x80) >> 7;
        ch1Val |= ch1Val & 0xFFF;*/

        ch1Val = 0;
        ch1Val = (dataCH1[1]<< 8) & 0b111100000000; //merge data[1] & data[2] to get result
        ch1Val |=  (dataCH1[2] & 0xff); 
        
        sleep(1);
        cout << "The Result is - Ch0 = " << ch0Val << " | Ch1 = " << ch1Val << endl;
        
    }
    return 0;
}

