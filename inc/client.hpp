/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:21:19 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/27 05:48:13 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP 

# include <iostream>
# include <string>
# include <vector>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <poll.h>
# include <csignal>
# include "utils.hpp"

class Server;

class Client
{
	private:
		int 						fd;
		std::string					UserIP;
		std::string					message;
		std::vector<std::string>	arguments;
	public:
		Client();
		Client(const Client &other);
		Client &operator=(const Client &other);
		~Client();

		int				getFd();
		std::string		getIp();
		// std::string		getMessage();
		// void			setMessage(std::string i);
		void			setIp(std::string i);
		void			setFd(int n);
		
		void	appendMessage(const std::string &buff);
		bool	hasLine();
		std::string takeCmd();
		std::string	takeLine();

		void		join();
};


#endif