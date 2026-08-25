#pragma once
#include "Client.hpp"

#include <string>
#include <iostream>
#include <map>

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
	void readCommand(std::string buffer);

private:
	int _serverFd;
	uint16_t _port;
	std::string _password;
	std::map<int, Client> _clients;
};
