#pragma once
#include <netinet/in.h>

class Client
{
public:
	Client();
	~Client();

	void setAddr(sockaddr_in address);
	sockaddr_in getAddr();

private:
	sockaddr_in _addr;
};
