#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <string>

#define MY_SOCK_PATH "/somepath"
#define LISTEN_BACKLOG 50

extern int	g_server_status;

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)
class server
{
    public :
        server(char *port, char *password);
        ~server();
    private :
        int _fd;
        int _epollfd;
} ;