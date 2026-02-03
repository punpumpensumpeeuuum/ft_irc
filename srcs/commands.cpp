/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 03:02:56 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/03 01:56:16 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

void	Client::join()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.size() != 1 && arguments.size() != 2)
		return printMessage(ERR_NEED_MORE_PARAMS);
	std::string cname = arguments[0];
	if (cname.empty() || cname[0] != '#')
		return printMessage(ERR_BAD_CHAN_MASK);
	Channel*	channel = server.findChannel(cname);
	if (channel)
	{
		if (channel->isAlreadyMember(this))
			return printMessage(ERR_USER_ON_CHANNEL);
		if (channel->hasPassword())
		{
			if (arguments.size() < 2)
				return printMessage(ERR_BAD_CHANNEL_KEY);
			std::string	pass = arguments[1];
			if (pass != channel->getPassword())
				return printMessage(ERR_BAD_CHANNEL_KEY);
		}
		if (!channel->isInvited(this) && (channel->isInviteOnly() || channel->isKicked(this)))
			return printMessage(ERR_INVITE_ONLY_CHAN);
		if (channel->getUserLimit() > 0 && channel->getUserCount() >= channel->getUserLimit())
			return printMessage(ERR_CHANNEL_IS_FULL);
		channel->addClient(this);
		channel->removeInvited(this);
		printMessage(JOINED_CHANNEL);
	}
	else
	{
		channel = &server.createNewChannel(cname);
		std::cout << channel->getName() << std::endl;
		channel->addClient(this);
		channel->setOp(this);
		printMessage(CHANNEL_CREATED);
		printMessage(JOINED_CHANNEL);
		printMessage(CHANNEL_OP);
	}
}

bool	Client::channelexist(std::string channelname)
{
	const std::vector<Channel> &channel_list = server.getChannelList();
	std::vector<Channel>::const_iterator it;
	for (it = channel_list.begin(); it != channel_list.end(); ++it)
	{
		if (it->getName() == channelname)
			return (true);
	}
	return (false);
}

void	Client::pass()
{
	if (passcheck || authenticatedcheck)
		return printMessage(ERR_ALREADY_REGISTERED);
	if (arguments.size() < 1)
		return printMessage(ERR_NEED_MORE_PARAMS);
	if (arguments.size() > 1)
		return printMessage(ERR_INVALID_PASSWORD);
	if (arguments.front() != server.getPass())
		return printMessage(ERR_PASSWD_MIS_MATCH);
	passcheck = true;
	printMessage(PASSWORD_SUCCESS);
	if (nickcheck && usercheck)
	{
		authenticatedcheck = true;
		printMessage(LOGIN_SUCCESS);
	}
}

bool	Client::validName(std::string str)
{
	if (str.length() < 3 || !isalpha(str[0]))
		return (false);
	for (size_t i = 0; i < str.length(); i++)
		if ((isalnum(str[i]) || str[i] == '-' || str[i] == '_') == false)
			return (false);
	return (true);
}

bool	Client::nickAlreadyExists(std::string str)
{
	std::vector<std::string> list = server.getcNickList();
	if (std::find(list.begin(), list.end(), str) != list.end())
		return (true);
	return (false);
}

void	Client::nick()
{
	if (nickcheck || authenticatedcheck)
		return printMessage(ERR_ALREADY_REGISTERED);
	if (arguments.size() < 1)
		return printMessage(ERR_NO_NICKNAME_GIVEN);
	if (arguments.size() > 1 || !validName(arguments[0]))
		return printMessage(ERR_ERRONEUS_NICKNAME);
	if (nickAlreadyExists(arguments[0]))
		return printMessage(ERR_NICKNAME_IN_USE);
	server.setNewcNick(cnick, arguments[0]);
	cnick = arguments[0];
	nickcheck = true;
	printMessage(NICKNAME_SUCCESS);
	if (passcheck && usercheck)
	{
		authenticatedcheck = true;
		printMessage(LOGIN_SUCCESS);
	}
}

void	Client::user()
{
	if (usercheck || authenticatedcheck)
		return printMessage(ERR_ALREADY_REGISTERED);
	if (arguments.size() < 4)
		return printMessage(ERR_NEED_MORE_PARAMS);
	if (!(arguments[1] == "0" || arguments[1] == "*"))
		return printMessage(ERR_UNKNOWN_COMMAND);
	if (arguments[2] != "*")
		return printMessage(ERR_UNKNOWN_COMMAND);
	std::string	nuser = arguments[0].substr(0, 12);
	std::string nrealname;
	if (arguments[3][0] == ':')
	{
		if (arguments[3].length() > 1)
			nrealname = arguments[3].substr(1);
		for (size_t i = 4; i < arguments.size(); i++)
		{
			if (i >= 5)
				nrealname += " ";
			nrealname += arguments[i];
		}
	}
	else
		return printMessage(ERR_UNKNOWN_COMMAND);
	if (!validName(nuser))
		return printMessage(ERR_ERRONEUS_USER);
	if (nrealname.length() <= 3)
		return printMessage(ERR_ERRONEUS_REAL_NAME);
	cuser = nuser;
	crealname = nrealname;
	usercheck = true;
	printMessage(USERNAME_SUCCESS);
	if (passcheck && nickcheck)
	{
		authenticatedcheck = true;
		printMessage(LOGIN_SUCCESS);
	}
}

// void	Client::quit()
// {
// 	if (arguments.size() < 1)
// 		return printMessage(ERR_NEED_MORE_PARAMS);
// 	if (arguments.size() > 1)
// 		return printMessage(ERR_INVALID_PASSWORD);
// 	if (arguments.front() != server.getPass())
// 		return printMessage(ERR_PASSWD_MIS_MATCH);
// 	passcheck = true;
// 	printMessage(PASSWORD_SUCCESS);
// 	if (nickcheck && usercheck)
// 	{
// 		authenticatedcheck = true;
// 		printMessage(LOGIN_SUCCESS);
// 	}
// 	return ;
// }
