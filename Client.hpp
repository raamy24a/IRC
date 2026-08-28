/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:37:08 by radib             #+#    #+#             */
/*   Updated: 2026/08/28 05:55:53 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <csignal>
#include "Channel.hpp"
#include <vector>

class Client
{
    public :
        Client(int fd);
        Client();
        void sendRegistration();
        ~Client();
        void parse(std::string parse);
        int get_clientfd();
        void addBuffer(char *buffer);
        std::string removeBuffer();
        void addClientToChannel(std::string parse, int cfd, const Server& server);

    private :
        std::string _username;
        std::string _nickname;
        std::vector<Channel> _channels;
        bool _operator;
        int _cfd;
        std::string _clientString;
} ;