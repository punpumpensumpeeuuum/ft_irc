/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/26 18:53:50 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/channel.hpp"

Channel::Channel()
{
	name = "Channel";
	password = "password";
	invinteonly = false;
	userlimit = 2;
}

Channel::Channel(const Channel &other)
{
	(void)other;
}

Channel &Channel::operator=(const Channel &other)
{
	(void)other;
	return (*this);
}

Channel::~Channel()
{
	// free things ig
}

