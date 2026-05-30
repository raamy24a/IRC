/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socks.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.42belgium.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 10:42:55 by radib             #+#    #+#             */
/*   Updated: 2026/05/30 10:46:51 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void smelly_socks(int port, fuckcpp password)
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(server_fd, );
	bind(server_fd, );
	listen(port, 67);
}