/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/05 18:54:07 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

Client::Client(Server &ser, int cc) : server(ser), csocket(cc)
{
	resolveHostname();
	this->cnick = "Random";
	this->fd = 0;
	this->userIP = "1.0.0.0";
	this->authenticatedcheck = false;
	this->passcheck = false;
	this->nickcheck = false;
	this->usercheck = false;
	this->cuser = "";
	this->crealname = "";
}

Client::Client(const Client &other) : server(other.server), csocket(other.csocket)
{
	fd = other.fd;
	cnick = other.cnick;
	userIP = other.userIP;
	message = other.message;
	arguments = other.arguments;
	authenticatedcheck = other.authenticatedcheck;
	passcheck = other.passcheck;
	nickcheck = other.nickcheck;
	usercheck = other.usercheck;
	cuser = other.cuser;
	crealname = other.crealname;
}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		fd = other.fd;
		cnick = other.cnick;
		userIP = other.userIP;
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

void	Client::resolveHostname()
{
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);

	if (getpeername(csocket, (struct sockaddr*)&addr, &addr_len) == 0)
		userIP = inet_ntoa(addr.sin_addr);
	else
		userIP = "unknown";
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
	return (this->userIP);
}

void	Client::setIp(std::string i)
{
	this->userIP = i;
}

std::string	Client::getNick()
{
	return (this->cnick);
}

bool	Client::getAuthenticated()
{
	return (this->authenticatedcheck);
}

void	Client::setNick(std::string n)
{
	this->cnick = n;
}

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

void	Client::clearbuff()
{
	this->message.clear();
	this->arguments.clear();
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

void	Client::handlecmd(std::string c)
{
	if (c.size() < 1)
		return ;
	size_t i = server.findCmd(c);
	switch (i)
	{
	case 1:
		pass();
		break;
	case 2:
		nick();
		break;
	case 3:
		user();
		break;
	case 4: 
		join();
		break;
	case 8:
		ping();
		break;
	// case 13:
	// 	help();
	// 	break;
	default:
		printMessage(ERR_UNKNOWN_COMMAND);
		break;
	}
	clearbuff();
}
