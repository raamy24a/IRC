#include "Client.hpp"

Client::Client()
{
	_inChan = false;
	_chanId = -1;
	_ctl = 0;
}
Client::~Client() {}

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
