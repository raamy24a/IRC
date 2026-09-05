#pragma once
#include <vector>
#include <map>
#include <sys/socket.h>
#include <iostream>

class Channel
{
public:
    Channel() {};
    Channel(int cfd, std::string name);

    void AddOperator(int cfd);
    bool isClientOperator(int cfd) const;
    bool AddClient(int cfd);
    void sendToChannel(std::string str, int sender_fd);

private:
    std::map<int, bool> _clients;
    std::string _fortnite;
    std::string _name;
    std::string _passwordStr;
    bool _inviteOnly;
    bool _topicOperator;
    bool _password;
    int _userLimit;
};
