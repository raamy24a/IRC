/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 01:37:06 by radib             #+#    #+#             */
/*   Updated: 2026/08/29 02:25:00 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void Channel::sendToChannel(std::string str)
{
    std::map<int,  bool>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        send((*it).first, str.c_str(), str.length(), 0);
        it++;
    }
}

Channel::Channel(int cfd, std::string name)
{
    _clients.insert(std::pair<int, bool>(cfd, true));
    _name = name;
    _passwordStr = "";
    _inviteOnly = 0;
    _topicOperator = 0;
    _password = 0;
    _userLimit = -1;
}

void Channel::AddOperator(int cfd)
{
    _clients[cfd] = true;
}
bool Channel::isClientOperator(int cfd) const
{
    return _clients.count(cfd);
}
void Channel::AddClient(int cfd)
{
    _clients.insert(std::pair<int, bool>(cfd, false));
}