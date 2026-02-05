/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:21:19 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/05 18:54:54 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP 

# include "messages.hpp"
# include "utils.hpp"
# include "server.hpp"

class Server;
class Channel;

class Client
{
	private:
		int 						fd;
		std::string					cnick;
		std::string					cuser;
		std::string					crealname;
		std::string					userIP;
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

		void			resolveHostname();
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
		void			clearbuff();

		void			pass();

		bool			validName(std::string str);
		bool			nickAlreadyExists(std::string str);
		void			nick();
		
		void			user();

		void			handlecmd(std::string c);
		bool			channelexist(std::string channelname);
		std::string		getFullMask();
		void			joiningMessage(const std::string& cname, Channel *channel);
		void			join();

		void			ping();
};


#endif