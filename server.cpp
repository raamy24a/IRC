#include "server.hpp"

server::server()
{
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(_fd, );

}

server::~server()
{
    close(_fd);
}