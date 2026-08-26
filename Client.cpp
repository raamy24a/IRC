/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 20:37:13 by radib             #+#    #+#             */
/*   Updated: 2026/08/25 02:35:13 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"

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
void Client::addBuffer(char *buffer)
{
    _clientString.append(buffer);
}

std::string Client::removeBuffer()
{
    std::string ret;
    if (_clientString.find('\r', 0) == -1)
        return (0);
    int Rpos = _clientString.find('\r', 0);
    ret = _clientString.substr(0, Rpos);
    return (ret);
}