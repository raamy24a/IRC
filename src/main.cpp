#include "Server.hpp"

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

// ./ircserv 1024 1234
// nc 127.0.0.1 1024 1234

/*
socket, setsockopt, bind, connect, listen, accept, send, recv, close, epoll
getsockname, getprotobyname, gethostbyname, getaddrinfo, freeaddrinfo
htons, htonl, ntohs, ntohl
inet_addr, inet_ntoa, inet_ntop
signal, sigaction, sigemptyset, sigfillset, sigaddset, sigdelset, sigismember
lseek, fstat, fcntl,
*/

// CR-LF (Carriage Return - Line Feed)

// On mIRC connection
// buffer == CAP LS 302
// CAPacity LiSt 302 (response 302 from RFC 1459)
