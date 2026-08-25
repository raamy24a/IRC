#include "Server.hpp"

// int g_sever_status = 1;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Error: Too much or not enough arguments." << std::endl;
        return (1);
    }

    Server a(argv[1], argv[2]);

    a.init();

    return (0);
}
