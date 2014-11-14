#include "Message.h"

#include <boost/archive/text_oarchive.hpp>

#include <boost/asio.hpp>

#include <iostream>
#include <boost/serialization/utility.hpp>
using namespace std;
int main()
{
    Message msg;
    //msg._a = "hello";
    //msg._b = "world";
    for(int i=0;i<10;i++)
    {
        getline(cin,msg._a);
        getline(cin,msg._b);

        boost::asio::streambuf buf;
    std::ostream os( &buf );
    boost::archive::text_oarchive ar( os );
    ar & msg;

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket( io_service );
    const short port = 1234;
    socket.connect(
            boost::asio::ip::tcp::endpoint(
                boost::asio::ip::address::from_string( "10.0.0.8" ),
                port
                )
            );

    const size_t header = buf.size();
    std::cout << "buffer size " << header << " bytes" << std::endl;

    // send header and buffer using scatter
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back( boost::asio::buffer(&header, sizeof(header)) );
    buffers.push_back( buf.data() );
    const size_t rc = boost::asio::write(
            socket,
            buffers
            );
    std::cout << "wrote " << rc << " bytes" << std::endl;;
        
    }

    
}