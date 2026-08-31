/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:37:08 by radib             #+#    #+#             */
/*   Updated: 2026/08/31 06:15:35 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <csignal>
#include "Channel.hpp"
#include <vector>
#include <sstream>

class Server;

class Client
{
    public :
        Client(int fd);
        Client();
        void sendRegistration();
        ~Client();
        void parse(std::string parse, Server& server);
        int get_clientfd();
        bool IsClient(std::string client_name);
        void addBuffer(char *buffer, Server& server);
        std::string removeBuffer(Server& server);
        void addClientToChannel(std::string parse, Server& server);
        void addClientHelper(std::string token, int _cfd, Server& server);


    private :
        std::string _username;
        std::string _nickname;
        std::vector<Channel> _channels;
        bool _operator;
        int _cfd;
        std::string _clientString;
} ;