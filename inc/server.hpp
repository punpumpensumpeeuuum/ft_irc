/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 01:41:47 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/29 20:02:58 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP 

# include "messages.hpp"
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
		std::string			port;
		int					serverSocket;
		static bool			signal;

		void		cmdlistInit(std::vector<std::string>& cmdl);
	public:
		Server();
		Server(std::string pooort, const std::string paaasss);
		Server(const Server &other);
		Server &operator=(const Server &other);
		~Server();
	
		std::vector<Channel>	getChannelList();
		Channel&				createNewChannel(std::string cname);
		Channel* 				findChannel(std::string& name);

		void		Init();
		void		CloseServer();
		void		CloseClient(int fd);
		static void	SignalHandler(int signum);
		Client*		getClientByFd(int fd);
		void		AcceptClient();
		void		ReceiveData(int fd);

		void					handlecmd(std::string c, Client& cli);
};


#endif