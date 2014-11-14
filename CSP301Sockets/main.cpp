#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    if (argc!=2)
    {
        std::cerr << "Usage: client <host>" << std::endl;
        return 1;
    }
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1],"daytime");
    tcp::resolver::iterator endpointIterator=resolver.resolve(query);
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpointIterator);
    
    for (; ; )
    {
        boost::array<char, 128> buffer;
        boost::system::error_code error;
        size_t len=socket.read_some(boost::asio::buffer(buffer),error);
        if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
        else if (error)
            throw boost::system::system_error(error); // Some other error.
        
        std::cout.write(buffer.data(), len);
    }
    return 0;
}