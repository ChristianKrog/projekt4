#include "arduinoIF.h"

UART::seriel_com::seriel_com(unsigned int baudrate,int stopbits,int parity)
	:io(), port(io,"/dev/ttyS0")
{
	port.set_option(asio::serial_port_base::baud_rate(baudrate)); 

						//Det her må kunne gøres smartere
	if (stopbits == 1)
	{
		asio::serial_port_base::stop_bits 	Stop(asio::serial_port_base::stop_bits::one);
		port.set_option(Stop);
	}
	else if (stopbits == 2)
	{
		asio::serial_port_base::stop_bits 	Stop(asio::serial_port_base::stop_bits::two);
		port.set_option(Stop);
	}

	if (parity == 0)
	{
		asio::serial_port_base::parity 		pari(asio::serial_port_base::parity::none);	//chooses if parity bit is used
		port.set_option(pari);
	}
	else if(parity == 1)
	{
		asio::serial_port_base::parity 		pari(asio::serial_port_base::parity::odd);	//chooses if parity bit is used
		port.set_option(pari);

	}
	else if(parity == 2)
	{
		asio::serial_port_base::parity 		pari(asio::serial_port_base::parity::even);	//chooses if parity bit is used
		port.set_option(pari);

	}
	port.close();
		
}

UART::seriel_com::~seriel_com()
{

}

void UART::seriel_com::send_char(char ch)
{			
	port.open("/dev/ttyS0");		
	asio::write(port,asio::buffer(&ch,1));  //Sender en char ud på seriel porten
	port.close();
	
}

void UART::seriel_com::send_string(std::string *str)
{
				//c_str() giver en pointer til en null terminated string (en c string)
	port.open("/dev/ttyS0");
	asio::write(port,asio::buffer(str->c_str(),str->size()));		
	port.close();
}

char UART::seriel_com::read_char()
{
	char c;

	port.open("/dev/ttyS0");
    asio::read(port, asio::buffer(&c,1));            //Blocking Read
	port.close();

	return c;
}

std::string UART::seriel_com::read_string()
{
	char c;
    std::string str;
	port.open("/dev/ttyS0");
    while (str.back() != '\n')
	{
		asio::read(port, asio::buffer(&c,1));            //Blocking Read
		str.push_back(c);
    }
	port.close();
	return str;
}
