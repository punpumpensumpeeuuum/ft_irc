/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/03 01:57:33 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/channel.hpp"

Channel::Channel()
{
	name = "Channel";
	password = "";
	invinteonly = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(std::string n) : name(n)
{
	password = "";
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
	name = other.name;
	password = other.password;
	invinteonly = other.invinteonly;
	userlimit = other.userlimit;
	userCount = other.userCount;
	clientmembers = other.clientmembers;
	invitedmembers = other.invitedmembers;
	operators = other.operators;
	kicked = other.kicked;
}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		name = other.name;
		password = other.password;
		invinteonly = other.invinteonly;
		userlimit = other.userlimit;
		userCount = other.userCount;
		clientmembers = other.clientmembers;
		invitedmembers = other.invitedmembers;
		operators = other.operators;
		kicked = other.kicked;
	}
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
	clientmembers.insert(cli);
	userCount++;
}

bool		Channel::isOperator(Client *cli)
{
	if (operators.find(cli) != operators.end())
		return (true);
	return (false);
}

void		Channel::setOp(Client* cli)
{
	if (!isOperator(cli))
		operators.insert(cli);
	return ;
}

bool		Channel::isAlreadyMember(Client *cli)
{
	// for (size_t i = 0; i < clientmembers.size(); i++)
	// {
	// 	if (clientmembers[i] == cli)
	// 		return (true);
	// }
	// return (false);
	if (clientmembers.find(cli) != clientmembers.end())
		return (true);
	return (false);
}

bool		Channel::isInviteOnly()
{
	return (this->invinteonly);
}

bool		Channel::isInvited(Client *cli)
{
	if (invitedmembers.find(cli) != invitedmembers.end())
		return (true);
	return (false);
}

bool		Channel::isKicked(Client *cli)
{
	if (kicked.find(cli) != kicked.end())
		return (true);
	return (false);
}

bool		Channel::hasPassword()
{
	if (password.empty())
		return (false);
	return (true);
}

std::string		Channel::getPassword()
{
	return (this->password);
}

int			Channel::getUserLimit()
{
	return (this->userlimit);
}

int			Channel::getUserCount()
{
	return (this->userCount);
}

void		Channel::removeInvited(Client *cli)
{
	invitedmembers.erase(cli);
}