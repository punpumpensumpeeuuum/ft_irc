/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/01 19:05:00 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

Client::Client(Server &ser, int cc) : server(ser), csocket(cc)
{
	this->cnick = "Random";
	this->fd = 0;
	this->UserIP = "1.0.0.0";
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
	UserIP = other.UserIP;
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

void	Client::handlecmd(std::string c)
{
	if (c.size() < 1)
		return ;
	size_t i = server.findCmd(c);
	switch (i)
	{
	case 0: 
		join();
		break;
	case 3:
		nick();
		break;
	case 4:
		user();
		break;
	case 11:
		pass();
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
