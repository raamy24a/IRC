#include "server.hpp"
#include <sys/socket.h>
#include <stdint.h>
#include <iostream>
#include <sys/epoll.h>

server::server(char *port, char *password)
{
    // setsockopt(_fd, );
    int                 _fd, cfd, _epollfd;
    socklen_t           peer_addr_size;
    sockaddr_in  my_addr{}, peer_addr;
    if (std::atoi(port) > UINT16_MAX || std::atoi(port) < 0)
        throw("erreur sur le port");
    uint16_t port_uint = std::atoi(port);
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    const int enable = 1;
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw("Error");
    if (_fd == -1)
        handle_error("socket");

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
    _epollfd = epoll_create(67);
    epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = _fd;
    // check return value epoll_ctl(edgecaserror)
    epoll_ctl(_epollfd, EPOLL_CTL_ADD, _fd, &ev);
    epoll_event events[10];
    // check return value epoll_ctl(edgecaserror)
    while (g_server_status)
    {
        int eventAmmount = epoll_wait(_epollfd, events, 10, 0);
        int i = 0;
        while (i < eventAmmount)
        {
            if (events[i].data.fd == _fd)
                epoll_ctl(_epollfd, EPOLL_CTL_ADD, _fd, &ev);
            else if (events[i].events &EPOLLIN)
            {
                char buffer[200];
                int readbuff = 1;
                memset(buffer, 0, 200);
                if (readbuff = read(events[i].data.fd, &buffer, 199))
                    printf("%s", buffer);
                else
                {
                    epoll_ctl(_epollfd, EPOLL_CTL_DEL, _fd, &ev);
                    close(events[i].data.fd);
                }
            }
            else if (events[i].events &EPOLLHUP || events[i].events &EPOLLERR)

        }
    }






    cfd = accept(_fd, (struct sockaddr *) &peer_addr, &peer_addr_size);
   
    
    
    while (readbuff)
    {
        printf("\nboucle :\n");
        readbuff = read(cfd, &buffer, 199);
        buffer[readbuff] = '\0';
        printf("%s", buffer);
    }
    std::cout << buffer << std::endl;
    if (cfd == -1)
        handle_error("accept");

    /* Code to deal with incoming connection(s)... */

    if (close(_fd) == -1)
        handle_error("close");
    (void)password;
}

server::~server()
{
    close(_fd);
    std::cout << "server destructor called" << std::endl;
}