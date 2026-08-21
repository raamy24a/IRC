#include <sys/socket.h>
#include <unistd.h>

class server
{
    public :
        server();
        ~server();
    private :
        int _fd;
} ;