/***********************************************
* MSYS, LAB 12, Del 2                          *
* Software UART sender.                        *
*                                              *
* Henning Hargaard 20/11 2015                  *
************************************************/
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define DDR   DDRE
#define PORT PORTE
#define PINNR 1
#define BAUD  9600

#define NO_us 1000000/BAUD

// 8 data bit, no parity, 1 stop bit
void SendCharSW(char Tegn)
{
  //  <------------- Skriv kode her
}

int main(void)
{
	UCSR0B = 0;
	DDR |= (1<<PINNR);
	while(1)
	{
		SendCharSW('A');
		SendCharSW('B');
		SendCharSW('C');
	}
}