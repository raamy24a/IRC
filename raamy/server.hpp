#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <vector>
#include "client.hpp"

#define MY_SOCK_PATH "/somepath"
#define LISTEN_BACKLOG 50

extern volatile int	g_server_status;

class server
{
    public :
        server(char *port, char *password);
        ~server();
        void addClientToServ(int fd);
    private :
        int _fd;
        int _epollfd;
        std::vector<client> _clientVector;
} ;
