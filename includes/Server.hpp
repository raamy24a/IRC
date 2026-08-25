#pragma once
#include <string>
#include <iostream>

#include <unistd.h>
#include <cstdlib>

#include <sys/socket.h>
#include <netinet/in.h>
// #include <netdb.h>

#include <sys/epoll.h>

class Server
{
public:
	Server();
	Server(std::string port, std::string pswd);
	~Server();

	void init();

private:
	uint16_t _port;
	std::string _password;
};
