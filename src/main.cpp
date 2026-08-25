#include "Server.hpp"

// int g_sever_status = 1;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Error: Too much or not enough arguments." << std::endl;
        return (1);
    }

    Server serv(argv[1], argv[2]);

    try
    {
        serv.init();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return (0);
}

// ./ircserv 1024 pswd
// nc 127.0.0.1 1024
