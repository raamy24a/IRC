#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <sys/socket.h>
#include <stdint.h>
#include <iostream>
#include <sys/epoll.h>
#include "Client.hpp"
#include "Channel.hpp"
#include <map>
#include <csignal>
#define MY_SOCK_PATH "/somepath"
#define LISTEN_BACKLOG 50

extern volatile std::sig_atomic_t g_server_status;

class Server
{
    public :
        Server(char *port, char *password);
        ~Server();
        bool AddClient(std::string chan, int cfd);
        void addClientToServ();
        bool isChannel(std::string str) const;
        void addClientToChan(std::string channel_name, int cfd);
        void sendToChannel(std::string str, std::string channel_name);
        void createChannel(std::string channel_name, int cfd);
        int  returnClientFd(std::string client_name);

    private :
        int _fd;
        int _epollfd;
        std::map<int, Client> _clientMap;
        std::map<std::string, Channel> _channels;
} ;
bool isChannelValid(std::string str);

