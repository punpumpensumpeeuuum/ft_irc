/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:21:19 by buddy2            #+#    #+#             */
/*   Updated: 2026/03/20 06:12:33 by buddy2           ###   ########.fr       */
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
		bool						disconnected;
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
		std::string		getCuser();
		bool			getAuthenticated();
		// std::string	getMessage();
		// void			setMessage(std::string i);
		void			setNick(std::string n);
		void			setIp(std::string i);
		void			setFd(int n);
		bool			isDisconnected();
		
		void			appendMessage(const std::string &buff);
		bool			hasLine();
		std::string		takeCmd();
		std::string		takeLine();
		void			clearbuff();

		void			fast();
		void			fast2();
		
		void			help();

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

		void			quit();

		void			part();

		void			msg();

		void			ping();

		void			kick();

		void			topic();

		void			mode();
		void			modeInvite(Channel *chanchan);
		void			modeTopic(Channel *chanchan);
		void			modeKeyword(Channel *chanchan);
		void			modeLimit(Channel *chanchan);
		void			modeOperator(Channel *chanchan);

		void			list();
};


#endif


/*
	oss << "PASS <password>						|| Enter server password" << std::endl;
	oss << "NICK <nickname>						|| Set a new nickname" << std::endl;
	oss << "USER <username> * * : <realname>	|| Set your username and real name" << std::endl;
	if (this->authenticatedcheck == true)
	{
		oss << "NICK <nickname>						|| Set a new nickname" << std::endl;
		oss << "PING <token>						|| Ping the server" << std::endl;
		oss << "QUIT <reason>						|| Leave the server" << std::endl;
		oss << "JOIN <channel>						|| Join a channel" << std::endl;
		oss << "PART <channel>						|| Leave a channel" << std::endl;
		oss << "KICK <channel> <user>				|| Kicks an user from a channel" << std::endl;
		oss << "INVITE <nick> <channel>				|| Invites an user to a channel" << std::endl;
		oss << "MSG <nick/channel> : <message>		|| Sends a message to an user or a channel" << std::endl;
		oss << "MODE <channel> <modes> [params]		|| Changes channel's mode" << std::endl;
		oss << "Modes:								||" << std::endl;
		oss << "	i - Invite only					||" << std::endl;
		oss << "	t - Only ops can change topics	||" << std::endl;
		oss << "	k - Set/remove channel password	||" << std::endl;
		oss << "	l - Set/remove user limit		||" << std::endl;
		oss << "	o - Give/take operator status	||" << std::endl;
		oss << "TOPIC <channel>						|| Sees the channel's topic" << std::endl;
		oss << "TOPIC <channel> <newtopic>			|| Change the channel's topic" << std::endl;
	}
*/