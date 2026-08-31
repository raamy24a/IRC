/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 01:37:06 by radib             #+#    #+#             */
/*   Updated: 2026/09/01 00:09:28 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"


static void sendDEBUG(int __fd, const void *__buf, size_t __n, int __flags)
{
    std::cout << "send: " << std::string(static_cast<const char*>(__buf), __n) << std::endl;
    send(__fd, __buf, __n, __flags);
}

void Channel::sendToChannel(std::string str, int sender_fd)
{
    std::map<int,  bool>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if (sender_fd != (*it).first)
            sendDEBUG((*it).first, str.c_str(), str.length(), 0);
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
bool Channel::AddClient(int cfd)
{
    if (_clients.count(cfd))
        return false;
    _clients.insert(std::pair<int, bool>(cfd, false));
    return true;
}