/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:33:00 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/27 05:06:11 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

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
# include "utils.hpp"


class Client;

class Channel
{
private:
	std::vector<Client>	clientmembers;
	std::string			name;
	std::string			password;
	bool				invinteonly;
	int					userlimit;
public:
		Channel();
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);
		~Channel();
};

#endif