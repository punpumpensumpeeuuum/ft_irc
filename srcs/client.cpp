/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/30 06:33:34 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

Client::Client(Server &ser, int cc) : server(ser), csocket(cc)
{
	this->nick = "Random";
	this->fd = 0;
	this->UserIP = "1.0.0.0";
}

Client::Client(const Client &other) : server(other.server), csocket(other.csocket)
{
	fd = other.fd;
}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		fd = other.fd;
		nick = other.nick;
		UserIP = other.UserIP;
		message = other.message;
		arguments = other.arguments;
		csocket = other.csocket;
	}
	return (*this);
}

Client::~Client()
{
	// free things ig
}

int	Client::getFd()
{
	return (this->fd);
}

void	Client::setFd(int n)
{
	this->fd = n;
}

std::string	Client::getIp()
{
	return (this->UserIP);
}

void	Client::setIp(std::string i)
{
	this->UserIP = i;
}

std::string	Client::getNick()
{
	return (this->nick);
}

bool	Client::getAuthenticated()
{
	return (this->authenticatedcheck);
}

void	Client::setNick(std::string n)
{
	this->nick = n;
}

// void	Client::setMessage(std::string i)
// {
// 	this->message = i;
// }

// std::string	Client::getMessage()
// {
// 	return (this->message);
// }

bool	Client::hasLine()
{
	return (message.find("\r\n") != std::string::npos);
}

void	Client::appendMessage(const std::string &buff)
{
	message += buff;	
}

std::string Client::takeLine()
{
	size_t p = message.find("\r\n");
	std::string line = message.substr(0,p);
	message.erase(0, p + 2);
	return (line);
}

std::string Client::takeCmd()
{
	if (!hasLine())
		return "";
	std::string line = takeLine();
	if (line.empty())
		return "";
	arguments = Utils::split(line, ' ');
	if (arguments.empty())
		return "";
	std::string cmd = arguments[0];
	for (size_t i = 0; i < cmd.length(); i++)
		cmd[i] = std::toupper(cmd[i]);
	arguments.erase(arguments.begin());
	return (cmd);
}

void	Client::join()
{
	if (!authenticatedcheck)
	{
		printMessage(ERR_NOT_AUTHENTICATED);
		return ;
	}
	if (arguments.size() != 1 && arguments.size() != 2)
	{
		printMessage(ERR_NEED_MORE_PARAMS);
		return ;
	}
	std::string cname = arguments[0];
	if (cname.empty() || cname[0] != '#')
	{
		printMessage(ERR_BAD_CHAN_MASK);
		return ;
	}
	Channel* channel = server.findChannel(cname);
	if (channelexist(cname)) // find if channel exist
	{
		channel->addClient(this);
		std::cout << "JOINING   CHANNEK" << std::endl;
	}
	else // create a channel
	{
		channel = &server.createNewChannel(cname);
		channel->addClient(this);
		channel->setOp(this);
		printMessage(CHANNEL_CREATED);
		printMessage(JOINED_CHANNEL);
		printMessage(CHANNEL_OP);
	}
}

bool	Client::channelexist(std::string channelname)
{
	const std::vector<Channel> &channel_list = server.getChannelList();
	std::vector<Channel>::const_iterator it;
	for (it = channel_list.begin(); it != channel_list.end(); ++it)
	{
		if (it->getName() == channelname)
			return (true);
	}
	return (false);
}