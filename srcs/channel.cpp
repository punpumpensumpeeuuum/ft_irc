/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/09 03:54:54 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/channel.hpp"

Channel::Channel()
{
	name = "Channel";
	password = "";
	inviteonly = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(std::string n) : name(n)
{
	password = "";
	inviteonly = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(std::string n, std::string p) : name(n), password(p)
{
	inviteonly = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(const Channel &other)
{
	name = other.name;
	password = other.password;
	inviteonly = other.inviteonly;
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
		inviteonly = other.inviteonly;
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
	clientmembers.push_back(cli);
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
	return std::find(clientmembers.begin(), clientmembers.end(), cli) != clientmembers.end();
}

bool		Channel::isInviteOnly()
{
	return (this->inviteonly);
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
	if (!cli)
		return ;
	invitedmembers.erase(cli);
}

std::vector<Client*>&	Channel::getClients()
{
	return (clientmembers);
}

void		Channel::broadcast(std::string str, Client* except)
{
	for (std::vector<Client*>::iterator it = clientmembers.begin(); it != clientmembers.end(); ++it)
    {
		if (*it != except)
			(*it)->messageClient(str);
	}
}

void Channel::removeClient(Client *cli)
{
	std::vector<Client*>::iterator it = std::find(clientmembers.begin(), clientmembers.end(), cli);
	if (it != clientmembers.end())
	{
		clientmembers.erase(it);
		userCount--;
	}
	operators.erase(cli);
	invitedmembers.erase(cli);
}

Client*		Channel::getOnlyClient()
{
	if (clientmembers.size() == 1)
		return (clientmembers.front());
	return (NULL);
}