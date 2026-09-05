#include "Server.hpp"

volatile std::sig_atomic_t g_server_status = 1;

void handler(int sig)
{
    (void)sig;
    g_server_status = 0;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, handler);
    if (argc != 3)
        return (std::cout << "Error: Not enough or too much arguments" << std::endl, 0);
    try
    {
        Server a(argv[1], argv[2]);
    }
    catch (const char *msg)
    {
        std::cout << "Caught string literal: " << msg << std::endl;
    }
}
