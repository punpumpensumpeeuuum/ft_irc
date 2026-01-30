/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:33:00 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/29 20:03:04 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "messages.hpp"
# include "client.hpp"
# include "utils.hpp"


class Client;

class Channel
{
private:
	std::vector<Client*>	clientmembers;
	std::vector<Client*>	operators;
	std::string			name;
	std::string			password;
	bool				invinteonly;
	int					userlimit;
	int					userCount;
public:
		Channel();
		Channel(std::string n);
		Channel(std::string n, std::string p);
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);
		~Channel();

		std::string		getName() const;
		bool			isOperator(Client* cli);
		void			addClient(Client* cli);
		void			setOp(Client* cli);
};

#endif