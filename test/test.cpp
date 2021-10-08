#include <asio.hpp>
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <thread>
asio::io_context io;
std::thread rendered;
volatile bool isRunning = false;
void clear()
{
    system(
#ifdef WIN32
            "cls"
#else
            "clear"
#endif
          );
}
void delay(int second) { asio::steady_timer(io, asio::chrono::seconds(second)).wait(); }
void render()
{
    for (; isRunning; delay(1))
    {
        clear();
        std::cout << "QwQ\nQvQ\nNephren Kawaii!\n";
        std::cout.flush();
    }
}
void hnd(int)
{
    isRunning = false;
    if (rendered.joinable())
        rendered.join();
    exit(0);
}
int main()
{
    signal(SIGINT, hnd);
    isRunning = true;
    rendered = std::thread(render);
    while (isRunning);
    if (rendered.joinable())
        rendered.join();
    return 0;
}

