/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marada <marada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/03/20 18:54:38 by marada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/channel.hpp"

Channel::Channel()
{
	name = "Channel";
	topic = "";
	keyword = "";
	inviteonly = false;
	topicOp = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(std::string n) : name(n)
{
	topic = "";
	keyword = "";
	inviteonly = false;
	topicOp = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(std::string n, std::string p) : name(n), keyword(p)
{
	topic = "";
	inviteonly = false;
	topicOp = false;
	userlimit = 2;
	userCount = 0;
}

Channel::Channel(const Channel &other)
{
	name = other.name;
	keyword = other.keyword;
	inviteonly = other.inviteonly;
	topicOp = other.topicOp;
	userlimit = other.userlimit;
	userCount = other.userCount;
	clientmembers = other.clientmembers;
	invitedmembers = other.invitedmembers;
	operators = other.operators;
	kicked = other.kicked;
	topic = other.topic;
}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		name = other.name;
		keyword = other.keyword;
		inviteonly = other.inviteonly;
		topicOp = other.topicOp;
		userlimit = other.userlimit;
		userCount = other.userCount;
		clientmembers = other.clientmembers;
		invitedmembers = other.invitedmembers;
		operators = other.operators;
		kicked = other.kicked;
		topic = other.topic;
	}
	return (*this);
}
Channel::~Channel()
{
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

void	Channel::addKickClient(Client *cli)
{
	kicked.insert(cli);
}

bool	Channel::removeOp(Client *client)
{
	size_t removed = operators.erase(client);
	return (removed > 0);
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

bool		Channel::isTopicOpOnly()
{
	return (this->topicOp);
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

bool		Channel::hasKeyword()
{
	if (keyword.empty())
		return (false);
	return (true);
}

std::string		Channel::getKeyword()
{
	return (this->keyword);
}

void		Channel::setKeyword(std::string str)
{
	this->keyword = str;
}

int			Channel::getUserLimit()
{
	return (this->userlimit);
}

void		Channel::setUserLimit(int LIMIT)
{
	this->userlimit = LIMIT;
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

void		Channel::setInvited(Client* cli)
{
	if (!isInvited(cli))
		invitedmembers.insert(cli);
	return ;
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
	if (!cli)
		return ;
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

void	Channel::switchInvite()
{
	this->inviteonly = !(this->inviteonly); 
}

void	Channel::switchTopic()
{
	this->topicOp = !(this->topicOp); 
}

void	Channel::setTopic(std::string nt)
{
	this->topic = nt;
}

std::string	Channel::getTopic()
{
	if (this->topic.empty())
		return ("");
	return (this->topic);
}

void Channel::addMode(char mode)
{
	if (modes.find(mode) == std::string::npos)
		modes += mode;
}

void Channel::removeMode(char mode)
{
	size_t pos = modes.find(mode);
	if (pos != std::string::npos)
		modes.erase(pos, 1);
}

std::string Channel::getModes()
{
	if (modes.empty())
		return "";
	return "+" + modes;
}
