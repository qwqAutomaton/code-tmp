/*
https://www.noi.cn/xw/2019-08-16/715365.shtml
*/
#include <iostream>
#include "asio.hpp"
asio::io_context ctx;
int main()
{
    while (1)
    {
        try
        {
            asio::ip::tcp::socket socket(ctx);
            asio::connect(socket, asio::ip::tcp::resolver(ctx).resolve("www.noi.cn", "https"));
            asio::write(socket, asio::buffer("GET /xw/2019-08-16/715365.shtml HTTP/1.1\r\nHost: www.noi.cn\r\nUser-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:79.0) Gecko/20100101 Firefox/79.0\r\n\r\n"));
            std::array<char, 65536> buf;
            size_t len = socket.read_some(asio::buffer(buf));
            std::cout.write(buf.data(), len);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}