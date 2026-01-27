/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:41:47 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/27 05:50:59 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP 

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
# include <cstring>
# include "client.hpp"
# include "channel.hpp"
# include "utils.hpp"

class Channel;
class Client;

class Server
{
	private:
		std::vector<struct pollfd>	fds;
		std::vector<Client>			clientlist;
		std::vector<Channel>		channelist;
		std::vector<std::string>	cmdlist;

		std::string			pass;
		int					port;
		int					serverSocket;
		static bool			signal;

		void		cmdlistInit(std::vector<std::string>& cmdl);
	public:
		Server();
		Server(int pooort, const std::string paaasss);
		Server(const Server &other);
		Server &operator=(const Server &other);
		~Server();
	
		void		Init();
		void		CloseServer();
		void		CloseClient(int fd);
		static void	SignalHandler(int signum);
		Client*		getClientByFd(int fd);
		void		AcceptClient();
		void		ReceiveData(int fd);

		void		newChannel(std::string name);
		void		handlecmd(std::string c, Client& cli);
};


#endif