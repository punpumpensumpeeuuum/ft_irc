/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/27 06:13:42 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

Client::Client()
{
	this->fd = 0;
	this->UserIP = "1.0.0.0";
}

Client::Client(const Client &other)
{
	fd = other.fd;
}

Client &Client::operator=(const Client &other)
{
	if (this != &other)
	{
		fd = other.fd;
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

void	Client::setIp(std::string i)
{
	this->UserIP = i;
}

// void	Client::setMessage(std::string i)
// {
// 	this->message = i;
// }

std::string	Client::getIp()
{
	return (this->UserIP);
}

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
	if (arguments.size() != 1 && arguments.size() != 2)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return ;
	}
	std::string cname = arguments[0];
	if (cname.empty() || cname[0] != '#')
	{
		std::cout << "Bad channel name" << std::endl;
		return ;
	}
	std::cout << "CREATING NEW CHANNEK" << std::endl;
}