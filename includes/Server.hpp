#pragma once
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>

class Server
{
public:
	Server();
	Server(std::string port, std::string pswd);
	~Server();

	void init();

private:
	int _port;
	std::string _password;
};
