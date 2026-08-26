#pragma once
#include <string>
#include <vector>
#include <sstream>

#include <netinet/in.h>
#include <sys/epoll.h>

class Client
{
public:
	Client();
	Client(const Client &other);
	Client &operator=(const Client &other);
	~Client();

	int getFd();
	void setFd(int fd);

	sockaddr_in getAddr();
	void setAddr(sockaddr_in address);

	// Return true if client is in a channel
	bool isInChan();
	// Return the channel name
	std::string getChan();
	// Set the channel name where the client is
	void setChan(bool io, std::string id);

	void setCtl(int ctl);
	int getCtl();

	// Store a token in client vector
	void setToken(std::string str);
	std::vector<std::string> &getToken();

private:
	sockaddr_in _addr;
	bool _inChan;
	std::string _chanId;
	int _ctl;
	std::vector<std::string> _tokens;
	int _fd;
};
