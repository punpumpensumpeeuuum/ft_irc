/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:38:14 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/27 20:06:54 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.hpp"

int main(int ac, char** av)
{
	(void)av;
	try
	{
		if (ac != 3)
			throw (std::invalid_argument("Usage: ./ircserv <port> <password>"));
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		if (Utils::parseInput(av[1], av[2]) != 0)
			return (0);
		Server irc(av[1], av[2]);
		irc.Init();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}
