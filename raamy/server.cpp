#include "server.hpp"
#include <sys/socket.h>
#include <stdint.h>
#include <iostream>
#include <sys/epoll.h>
int volatile g_server_status = 1;

void server::addClientToServ(int fd)
{
    int cfd;
    // if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _fd, &ev) == -1)
    //     throw("epoll_ctl error");
    cfd = accept(_fd, 0, 0);
    client newClient(cfd);
    _clientVector.push_back(newClient);
}

server::server(char *port, char *password)
{
    // setsockopt(_fd, );
    int _fd, _epollfd;
    sockaddr_in my_addr;
    memset(&my_addr, 0, sizeof(sockaddr_in));
    if (std::atoi(port) > UINT16_MAX || std::atoi(port) < 0)
        throw("erreur sur le port");
    uint16_t port_uint = std::atoi(port);
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    const int enable = 1;
    if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        throw("Error setsockopt");
    if (_fd == -1)
        throw("Error socket");

    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(port_uint);
    if (bind(_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
        throw("Error bind");

    if (listen(_fd, LISTEN_BACKLOG) == -1)
        throw("Error listen");

    /* Now we can accept incoming connections one
        at a time using accept(2). */

    _epollfd = epoll_create(67);
    epoll_event ev;
    memset(&ev, 0, sizeof(epoll_event));

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
            {
                // addClientToServ();
            }
            else if (events[i].events & EPOLLIN)
            {
                char buffer[200];
                int readbuff = 1;
                memset(buffer, 0, 200);
                readbuff = read(events[i].data.fd, &buffer, 199);
                if (readbuff)
                    printf("%s", buffer);
                else
                {
                    epoll_ctl(_epollfd, EPOLL_CTL_DEL, _fd, &ev);
                    close(events[i].data.fd);
                }
            }
            else if (events[i].events & (EPOLLHUP | EPOLLERR))
                throw("EPOLLHUP or EPOLLERR error");
            i++;
        }
    }
    /* Code to deal with incoming connection(s)... */

    if (close(_fd) == -1)
        throw("Error close");
    (void)password;
}

server::~server()
{
    close(_fd);
    std::cout << "server destructor called" << std::endl;
}
