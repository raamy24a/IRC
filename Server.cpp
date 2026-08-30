#include "Server.hpp"
#include "Client.hpp"

bool isChannelValid(std::string str)
{
    if (str[0] == '#' || str[0] == '&' || str[0] == '!' || str[0] )
    {
        if (str.length() > 50)
            return false;
        else if (str.length() < 1 || str.find(',', 1) != std::string::npos || str.find(' ', 1) != std::string::npos, str.find(7, 1) != std::string::npos || str.find(':', 1) != std::string::npos)
            return false;
        return true;
    }
    return false;
}
bool Server::isChannel(std::string str) const
{
    if (_channels.count(str))
        return true;
    return false;
}

int  Server::returnClientFd(std::string client_name)
{
    std::map<int, Client>::iterator it = _clientMap.begin();

    while(it != _clientMap.end())
    {
        if ((*it).second.IsClient(client_name))
        {
            return ((*it).first);
        }
    }
    return (-1);
}

void Server::createChannel(std::string channel_name, int _cfd)
{
    _channels[channel_name] = Channel(_cfd, channel_name);
}
bool Server::AddClient(std::string chan, int cfd)
{
    if (_channels[chan].AddClient(cfd))
        return true;
    return false;
}
void Server::sendToChannel(std::string str, std::string channel_name)
{
    _channels[channel_name].sendToChannel(str);
}
void Server::addClientToChan(std::string channel_name, int cfd)
{
    _channels[channel_name].AddClient(cfd);

}


void Server::addClientToServ()
{
    int cfd = accept(_fd, 0, 0);


    epoll_event ev;
    memset(&ev, 0, sizeof(epoll_event));
    
    ev.events = EPOLLIN;
    ev.data.fd = cfd;
    if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, cfd, &ev) == -1)
        throw("epoll_ctl error");
    Client newClient(cfd);
    _clientMap.insert(std::pair<int, Client>(newClient.get_clientfd(), newClient));
    std::cout << "Client  : " << newClient.get_clientfd() << " Connected"<< std::endl; 
}

Server::Server(char *port, char *password)
{
    // setsockopt(_fd, );
    sockaddr_in  my_addr;
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
    if (bind(_fd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1)
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
                addClientToServ();
            }
            else if (events[i].events & EPOLLIN)
            {
                char buffer[200];
                int readbuff = 1;
                memset(buffer, 0, 200);
                readbuff = read(events[i].data.fd, &buffer, 199);
                if (readbuff)
                {
                    std::cout << "RECV :" << buffer;
                    _clientMap[events[i].data.fd].addBuffer(buffer, *this);
                }
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

Server::~Server()
{
    close(_fd);
    std::cout << "Server destructor called" << std::endl;
}