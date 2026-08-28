/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:37:13 by radib             #+#    #+#             */
/*   Updated: 2026/08/28 05:55:55 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"

Client::Client()
{
}
Client::Client(int fd)
{
    _cfd = fd;
    send(fd, ":ircserv CAP * LS :\r\n", 22, 0);
}

Client::~Client()
{
    
}
int Client::get_clientfd()
{
    return (_cfd);
}
void Client::addBuffer(char *buffer)
{
    _clientString.append(buffer);
    if (_clientString.find("\r\n", 0) == std::string::npos)
        return ;
    while (this->removeBuffer() != "");
}

void Client::sendRegistration() {
    std::string reply;

    reply = ":ircserv 001 " + _nickname + " :Welcome to the Internet Relay Network " + _nickname + "!" + _username + "@127.0.0.1\r\n";
    reply += ":ircserv 002 " + _nickname + " :Your host is ircserv, running version 1.0\r\n";
    reply += ":ircserv 003 " + _nickname + " :This server was created 2026-08-27\r\n";
    reply += ":ircserv 004 " + _nickname + " ircserv 1.0 i tkol\r\n";

    send(_cfd, reply.c_str(), reply.length(), 0);
}
void Client::parse(std::string parse, const Server& server)
{
    if (parse.find("NICK") == 0)
        this->_nickname = parse.substr(5, parse.length() - 2);
    else if (parse.find("USER") == 0)
        this->_username = parse.substr(5, parse.length() - 2);
    else if (parse.find("CAP END") == 0)
        this->sendRegistration();
    else if (parse.find("JOIN :") == 0)
        this->addClientToChannel(parse, this->_cfd, server);
        
}

std::string Client::removeBuffer()
{
    std::string ret;

    if (_clientString.find("\r\n", 0) == std::string::npos)
        return("");
    int Rpos = _clientString.find("\r\n", 0);
    ret = _clientString.substr(0, Rpos);
    this->parse(ret);
    _clientString.erase(0, Rpos + 2);
    std::cout << ret << std::endl;
    return (ret);
}