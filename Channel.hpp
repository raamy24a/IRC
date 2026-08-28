/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 01:37:08 by radib             #+#    #+#             */
/*   Updated: 2026/08/28 04:38:24 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <map>
#include <iostream>

class Channel
{
    public :
        Channel(int cfd, std::string name);
        void AddOperator(int cfd);
        bool isClientOperator(int cfd);
        void AddClient(int cfd);
        
    private :
        std::map<int,  bool> _clients;
        std::string _fortnite;
        std::string _name;
        bool _inviteOnly;
        bool _topicOperator;
        bool _password;
        
} ;
// je dois faire les commandes pour joins un channel et les reponses du serveur vers le client ;)
// int bool car key = fd et bool = operatorperms;