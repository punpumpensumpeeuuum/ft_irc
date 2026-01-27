/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:38:14 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/26 18:50:05 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.hpp"

int main(int ac, char** av)
{
	Server irc;
	(void)av;
	try
	{
		if (ac != 3)
			throw std::invalid_argument("Usage: ./IRC <port> <password>");
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		irc.Init();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
