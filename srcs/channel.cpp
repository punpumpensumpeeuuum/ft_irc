/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/29 19:11:21 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/channel.hpp"

Channel::Channel()
{
	name = "Channel";
	password = "password";
	invinteonly = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(std::string n) : name(n)
{
	password = "password";
	invinteonly = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(std::string n, std::string p) : name(n), password(p)
{
	invinteonly = false;
	userlimit = 2;
	userCount = 0;
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

std::string		Channel::getName() const
{
	return (this->name);
}

void		Channel::addClient(Client* cli)
{
	clientmembers.push_back(cli);
	userCount++;
}

bool		Channel::isOperator(Client *cli)
{
	for (size_t i = 0; i < operators.size(); i++)
	{
		if (operators[i] == cli)
			return (true);
	}
	return (false);
}

void		Channel::setOp(Client* cli)
{
	if (!isOperator(cli))
		operators.push_back(cli);
	return ;
}