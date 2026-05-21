#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>  

using boost::asio::ip::tcp;

int main() 
{
    try
    {
        boost::asio::io_context io_context;

        tcp::endpoint endpoint(tcp::v4(), 12345);
        tcp::acceptor acceptor(io_context, endpoint);

        std::cout << "Server started on port 12345..." << "\n";

        for(;;)
        {
            tcp::socket socket(io_context);
            
            boost::system::error_code ec;
            acceptor.accept(socket, ec); // 연결 수락

            if (!ec) {
                std::cout << "Client connected!" << "\n";
                
                std::string message_to_send = "Hello kkandull\n";
                
                boost::asio::write(socket, boost::asio::buffer(message_to_send), ec);
            }

        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}