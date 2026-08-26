#pragma once
#include <string>
#include <vector>

#include <netinet/in.h>
#include <sys/epoll.h>

class Client
{
public:
	Client();
	~Client();

	sockaddr_in getAddr();
	void setAddr(sockaddr_in address);

	bool isInChan();
	std::string getChan();
	void setChan(bool io, std::string id);

	void setCtl(int ctl);
	int getCtl();

private:
	sockaddr_in _addr;
	bool _inChan;
	std::string _chanId;
	int _ctl;
	std::vector<std::string> _tokens;
};
