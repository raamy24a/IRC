#include "Client.hpp"
#include <iostream>

Client::Client()
{
	_inChan = false;
	_chanId = -1;
	_ctl = 0;
	_fd = -1;
	_nick = "None";
}
Client::Client(const Client &other)
{
	_addr = other._addr;
	_inChan = other._inChan;
	_chanId = other._chanId;
	_ctl = other._ctl;
	_tokens = other._tokens;
	_fd = other._fd;
	_nick = other._nick;
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
		_nick = other._nick;
	}
	return (*this);
}
Client::~Client() {}

// FD
int Client::getFd() { return (_fd); }
void Client::setFd(int fd) { _fd = fd; }

// NICKNAME
std::string Client::getNick() { return (_nick); }
void Client::setNick(std::string nick) { _nick = nick; }

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
