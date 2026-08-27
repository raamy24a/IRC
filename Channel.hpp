/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 01:37:08 by radib             #+#    #+#             */
/*   Updated: 2026/08/27 12:15:16 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <iostream>

class Channel
{
    public :
        Channel();
    private :
        std::map<int,  bool> clients;
        
} ;
// je dois faire les commandes pour joins un channel et les reponses du serveur vers le client ;)
// int bool car key = fd et bool = operatorperms;