/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 01:37:06 by radib             #+#    #+#             */
/*   Updated: 2026/08/28 04:28:44 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(int cfd, std::string name)
{
    _clients.insert(std::pair<int, bool>(cfd, true));
    _name = name;
}
void Channel::AddOperator(int cfd)
{
    _clients[cfd] = true;
}
bool Channel::isClientOperator(int cfd)
{
    return _clients[cfd];
}
void Channel::AddClient(int cfd)
{
    _clients.insert(std::pair<int, bool>(cfd, false));
}