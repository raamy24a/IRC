#pragma once
#include "Client.hpp"

#include <string>
#include <iostream>
#include <map>
#include <sstream>

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
	// Server(const Server &Other);
	// Server operator=(const Server &Other);
	~Server();

	void init();

	void readCommand(int fd, std::string buffer);
	void handleCmds(Client user);

	void splitTokens(int fd, std::string buffer);
	void removeTokens(int fd);

	void joinChan(Client user);
	void msgClient(Client user);
	void changeNick(Client user);

private:
	int _serverFd;
	// Server Port
	uint16_t _port;
	// Server Password
	std::string _password;
	// Map of every Clients associated to their FDs
	std::map<int, Client> _clients;
};
