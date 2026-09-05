#pragma once
#include <map>
#include <csignal>
#include "Channel.hpp"
#include <vector>
#include <sstream>
#include <fcntl.h>

class Server;

class Client
{
public:
    Client();
    Client(int fd);
    ~Client();

    void sendRegistration();
    void parse(std::string parse, Server &server);
    int get_clientfd();
    bool IsClient(std::string client_name);
    void addBuffer(char *buffer, Server &server);
    std::string removeBuffer(Server &server);
    void addClientToChannel(std::string parse, Server &server);
    void addClientHelper(std::string token, int _cfd, Server &server);

    void setPasswordRight(bool b);
    bool getPasswordRight();

private:
    std::string _username;
    std::string _nickname;
    std::vector<Channel> _channels;
    bool _operator;
    int _cfd;
    std::string _clientString;
    bool _passwordRight;
};
