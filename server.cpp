#include "server.hpp"
#include <sys/socket.h>
#include <stdint.h>
#include <iostream>

server::server(std::string port)
{
    // setsockopt(_fd, );
    int                 _fd, cfd;
    socklen_t           peer_addr_size;
    sockaddr_in  my_addr, peer_addr;
    if (std::atoi(port.c_str()) > UINT16_MAX || std::atoi(port.c_str()) < 0)
        throw("erreur sur le port");
    uint16_t port_uint = std::atoi(port.c_str());
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd == -1)
        handle_error("socket");

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(port_uint);
    if (bind(_fd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1)
        handle_error("bind");

    if (listen(_fd, LISTEN_BACKLOG) == -1)
        handle_error("listen");

    /* Now we can accept incoming connections one
        at a time using accept(2). */

    peer_addr_size = sizeof(peer_addr);
    cfd = accept(_fd, (struct sockaddr *) &peer_addr, &peer_addr_size);
    char buffer[200];
    memset(buffer, 0, 200);
    read(cfd, &buffer, 199);
    printf("%s", buffer);
    std::cout << buffer << std::endl;
    if (cfd == -1)
        handle_error("accept");

    /* Code to deal with incoming connection(s)... */

    if (close(_fd) == -1)
        handle_error("close");
}

server::~server()
{
    close(_fd);
}