#include <boost/asio.hpp> 
#include <boost/asio/serial_port.hpp> 
#include <boost/asio/serial_port_base.hpp>
#include <iostream>
#include <string>
using namespace boost;

namespace UART
{
std::string read();

void send_char(char ch);

void send_string(std::string *str);

class seriel_com    //Er som standard sat til /dev/ttyS0 portene
    {   
    public:
        seriel_com(unsigned int baudrate,int stopbits,int parity);
        ~seriel_com();
        void send_char(char ch);
        void send_string(std::string *str);

        char read_char();
        std::string read_string();


    private:
        asio::io_service    				io;                                 
        asio::serial_port   				port;
    };
}