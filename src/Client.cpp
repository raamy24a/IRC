#include "Client.hpp"
#include <iostream>

Client::Client()
{
	_inChan = false;
	_chanId = -1;
	_ctl = 0;
	_fd = -1;
}
Client::Client(const Client &other)
{
	_addr = other._addr;
	_inChan = other._inChan;
	_chanId = other._chanId;
	_ctl = other._ctl;
	_tokens = other._tokens;
	_fd = other._fd;
}
Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		_addr = other._addr;
		_inChan = other._inChan;
		_chanId = other._chanId;
		_ctl = other._ctl;
		_tokens = other._tokens;
		_fd = other._fd;
	}
	return (*this);
}
Client::~Client() {}

int Client::getFd() { return (_fd); }
void Client::setFd(int fd) { _fd = fd; }

// ADDRESS
sockaddr_in Client::getAddr() { return (_addr); }
void Client::setAddr(sockaddr_in address) { _addr = address; }

// CHANNEL
bool Client::isInChan() { return (_inChan); }
std::string Client::getChan() { return (_chanId); }
void Client::setChan(bool io, std::string id)
{
	_chanId = id;
	_inChan = io;
}

// CTL
void Client::setCtl(int ctl) { _ctl = ctl; }
int Client::getCtl() { return (_ctl); }

// TOKEN
void Client::setToken(std::string str) { _tokens.push_back(str); }
std::vector<std::string> &Client::getToken() { return (_tokens); }
