/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:33:00 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/04 00:25:08 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <set>
# include "messages.hpp"
# include "client.hpp"
# include "utils.hpp"


class Client;

class Channel
{
private:
	std::set<Client*>	clientmembers;
	std::set<Client*>	invitedmembers;
	std::set<Client*>	operators;
	std::set<Client*>	kicked;
	std::string				name;
	std::string				password;
	bool					invinteonly;
	int						userlimit;
	int						userCount;
public:
		Channel();
		Channel(std::string n);
		Channel(std::string n, std::string p);
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);
		~Channel();

		std::set<Client*>	getClients();
		std::string			getName() const;
		bool				isOperator(Client* cli);
		void				addClient(Client* cli);
		void				setOp(Client* cli);
		bool				isAlreadyMember(Client* cli);
		bool				isInviteOnly();
		bool				isInvited(Client *cli);
		bool				isKicked(Client *cli);
		bool				hasPassword();
		std::string			getPassword();
		int					getUserLimit();
		int					getUserCount();

		void				removeInvited(Client *cli);
};

#endif