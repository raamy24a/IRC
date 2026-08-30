/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:37:13 by radib             #+#    #+#             */
/*   Updated: 2026/08/30 02:12:32 by radib            ###   ########.fr       */
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
}

Client::~Client()
{
    
}
int Client::get_clientfd()
{
    return (_cfd);
}
void Client::addBuffer(char *buffer, Server& server)
{
    _clientString.append(buffer);
    if (_clientString.find("\r\n", 0) == std::string::npos)
        return ;
    while (this->removeBuffer(server) != "");
}

void Client::sendRegistration() {
    std::string reply;
    reply = ":ircserv CAP "+ _nickname + " LS :\r\n";
    reply += ":ircserv 001 " + _nickname + " :Welcome to the Internet Relay Network " + _nickname + "!" + _username + "@127.0.0.1\r\n";
    reply += ":ircserv 002 " + _nickname + " :Your host is ircserv, running version 1.0\r\n";
    reply += ":ircserv 003 " + _nickname + " :This server was created 2026-08-27\r\n";
    reply += ":ircserv 004 " + _nickname + " ircserv 1.0 i tkol\r\n";
    reply += ":ircserv 422 " + _nickname + " :MOTD File is missing\r\n";
    reply += ":ircserv 376 " + _nickname + " :End of /MOTD command\r\n";
    std::cout << "SEND :" << reply << std::endl;
    send(_cfd, reply.c_str(), reply.length(), 0);
}
void Client::addClientToChannel(std::string parse, Server& server)
{
    if (parse.find(',', 0) != std::string::npos)
    {
        std::stringstream ss(parse);
	    std::string token;

	    while (getline(ss, token, ','))
        {
		    if (!token.empty() && isChannelValid(token) && !server.isChannel(token))
            {
                server.createChannel(token, _cfd);
            }
            else if (!token.empty() && isChannelValid(token) && server.isChannel(token))
                if (server.AddClient(token, _cfd))
                {
                    
                    std::string str = ':' + _nickname + '!' + _username + "@host JOIN " + token;        
                    server.sendToChannel(str, token);
                }
        }
    }
}

void Client::parse(std::string parse, Server& server)
{
    if (parse.find("NICK") == 0)
    {
        std::string params = parse.substr(5);
        this->_nickname = params.substr(0, params.find(' '));
    }
    else if (parse.find("CAP LS 302") == 0)
    {
        send(_cfd, ":ircserv CAP * LS :\r\n", 22, 0);
        std::cout << "SEND :" << ":ircserv CAP * LS :\r\n";
    }
    else if (parse.find("USER") == 0)
    {
        std::string params = parse.substr(5);
        this->_username = params.substr(0, params.find(' '));
        this->sendRegistration();
    }
    else if (parse.find("CAP END") == 0)
        return ;
    else if (parse.find("JOIN ") == 0)
        this->addClientToChannel(parse, server);
    else if (parse.find("PING") == 0)
    {
        std::cout << "SEND" << "PONG ircserv\r\n";
        send(_cfd, "PONG ircserv\r\n", 15, 0);
    }
    else if (parse.find("MODE") == 0)
    {
        std::string str;
        str = "MODE " + _username + " +i\r\n";
        std::cout << "SEND" << str;
        send(_cfd, str.c_str(), str.length(), 0);
    }
}

std::string Client::removeBuffer(Server& server)
{
    std::string ret;

    if (_clientString.find("\r\n", 0) == std::string::npos)
        return("");
    int Rpos = _clientString.find("\r\n", 0);
    ret = _clientString.substr(0, Rpos);
    this->parse(ret, server);
    _clientString.erase(0, Rpos + 2);
    // std::cout << ret << std::endl;
    return (ret);
}