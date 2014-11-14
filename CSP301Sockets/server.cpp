#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using boost::asio::ip::tcp;


class myClass
{
public:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive &ar,const unsigned int version)
    {
        ar & x;
        ar & y;
        ar & as;
    }
    int x;
    float y;
    std::string as;

    myClass(int xx, float yy, std::string asas):x(xx),y(yy),as(asas)
    {
        
    }
};

class tcpServer
{
public:
    tcpServer(boost::asio::io_service& io_service):acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4()))
    {
        
    }
};
std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service,tcp::endpoint(tcp::v4(),3000));
    std::string s=std::to_string(43);
    
    for (; ; )
    {
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        std::string message = make_daytime_string();
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(s), ignored_error);
    }
}