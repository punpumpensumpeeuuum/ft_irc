/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:33:00 by buddy2            #+#    #+#             */
/*   Updated: 2026/03/24 03:08:05 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <set>
# include <ctime>
# include "messages.hpp"
# include "client.hpp"
# include "utils.hpp"


class Client;

class Channel
{
private:
	std::vector<Client*>	clientmembers;
	std::set<Client*>		invitedmembers;
	std::set<Client*>		operators;
	std::set<Client*>		kicked;
	std::string				name;
	std::string				keyword;
	std::string				topic;
	bool					inviteonly;
	bool					topicOp;
	int						userlimit;
	int						userCount;
	std::string				modes;
public:
		Channel();
		Channel(std::string n);
		Channel(std::string n, std::string p);
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);
		~Channel();

		std::vector<Client*>&	getClients();
		std::string				getName() const;
		void					addClient(Client* cli);
		void					setOp(Client* cli);
		bool					isOperator(Client* cli);
		bool					isAlreadyMember(Client* cli);
		bool					isInviteOnly();
		bool					isTopicOpOnly();
		bool					isInvited(Client *cli);
		bool					isKicked(Client *cli);
		bool					hasKeyword();
		void					removeOp(Client *client);
		std::string				getKeyword();
		void					setKeyword(std::string str);
		int						getUserLimit();
		void					setUserLimit(int LIMIT);
		int						getUserCount();
		void					setTopic(std::string nt);
		std::string				getTopic();

		Client*					getOnlyClient(Client *expection);
		void					removeInvited(Client *cli);
		void					setInvited(Client *cli);
		void					broadcast(std::string str, Client* except);
		void					removeClient(Client *cli);
		void					addKickClient(Client *cli);
		void					switchInvite();
		void					switchTopic();

		void 					addMode(char mode);
		void 					removeMode(char mode);
		std::string				getModes();
};

#endif