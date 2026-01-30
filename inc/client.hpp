/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:21:19 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/30 06:34:22 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP 

# include "messages.hpp"
# include "utils.hpp"
# include "server.hpp"

class Server;

class Client
{
	private:
		int 						fd;
		std::string					nick;
		std::string					user;
		std::string					realname;
		std::string					UserIP;
		std::string					message;
		bool 						passcheck;
		bool 						nickcheck;
		bool 						usercheck;
		bool 						authenticatedcheck;
		std::vector<std::string>	arguments;
		Server						&server;
		int							csocket;
	public:
		Client(Server &ser, int cc);
		Client(const Client &other);
		Client &operator=(const Client &other);
		~Client();

		void 			printMessage(int nb);
		void			messageClient(std::string mes);
		void			messageClient(int nb);
		int				getFd();
		std::string		getIp();
		std::string		getNick();
		bool			getAuthenticated();
		// std::string	getMessage();
		// void			setMessage(std::string i);
		void			setNick(std::string n);
		void			setIp(std::string i);
		void			setFd(int n);
		
		void			appendMessage(const std::string &buff);
		bool			hasLine();
		std::string		takeCmd();
		std::string		takeLine();

		bool		channelexist(std::string channelname);
		void		join();
		void		nick();
		void		user();
		void		pass();
};


#endif