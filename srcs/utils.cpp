/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/31 23:50:22 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.hpp"

std::vector<std::string> Utils::split(const std::string &str, char splili)
{
	std::vector<std::string> args;
	std::string line;

	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] == splili)
		{
			if (!line.empty())
			{
				args.push_back(line);
				line.clear();
			}
		}
		else
		{
			line += str[i];
		}
	}
	if (!line.empty())
		args.push_back(line);
	return (args);
}

int Utils::parseInput(const std::string& portStr, const std::string& pass)
{
	if (pass.empty() || pass.find(' ') != std::string::npos)
		throw (std::invalid_argument("Error: empty password"));
	int port;
	std::stringstream portStream(portStr);
	if (!(portStream >> port) || !portStream.eof())
		throw (std::invalid_argument("Error: invalid port"));
	if (port < 1024 || port > 65535)
		throw (std::invalid_argument("Error: Port must be a number from 1024 to 65535"));
	return (0);
}