/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:37:08 by radib             #+#    #+#             */
/*   Updated: 2026/08/26 00:58:31 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Server.hpp"
#include <vector>

class Client
{
    public :
        Client(int fd);
        ~Client();
        int get_clientfd();
        void addBuffer(char *buffer);
        std::string removeBuffer();

    private :
        std::string _username;
        std::string _nickname;
        std::vector<> _channels;
        bool _operator;
        int _cfd;
        std::string _clientString;
} ;