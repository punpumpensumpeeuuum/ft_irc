/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frteixei <frteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 03:02:56 by buddy2            #+#    #+#             */
/*   Updated: 2026/03/20 16:25:48 by frteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

void	Client::help()
{
	std::ostringstream oss;

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

	messageClient(oss.str());
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
		if (!channel->isInvited(this) && channel->isInviteOnly())
			return printMessage(ERR_INVITE_ONLY_CHAN);
		if (channel->getUserLimit() > 0 && channel->getUserCount() >= channel->getUserLimit())
			return printMessage(ERR_CHANNEL_IS_FULL);
		channel->addClient(this);
		channel->removeInvited(this);
		joiningMessage(cname, channel);
		printMessage(JOINED_CHANNEL);
	}
	else
	{
		channel = server.createNewChannel(cname);
		channel->addClient(this);
		channel->setOp(this);
		joiningMessage(cname, channel);
		printMessage(CHANNEL_CREATED);
		printMessage(JOINED_CHANNEL);
		printMessage(CHANNEL_OP);
	}
}

std::string		Client::getFullMask()
{
	return (cnick + "~" + cuser + "@" + userIP);
}

void Client::joiningMessage(const std::string& cname, Channel *channel)
{
	std::string mask = getFullMask();
	std::string join_msg = ":" + mask + " JOIN " + cname + "\r\n";
	const std::vector<Client*>& clients = channel->getClients();

	for (std::vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		Client* client = *it;
		client->messageClient(join_msg);
	}
	this->messageClient(":" + this->cuser + " 324 " + cnick + " " + cname + "\r\n");

	std::ostringstream ts;
	ts << ":" << this->cuser << " 329 " << cnick << " " << cname << " " << std::time(0) << "\r\n";
	this->messageClient(ts.str());

	std::string channelnames;
	for (std::vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
		Client* client = *it;
		if (!channelnames.empty())
			channelnames += " ";
		if (channel->isOperator(client))
			channelnames += "@" + client->getNick();
		else
			channelnames += client->getNick();
	}
	this->messageClient(":" + this->cuser + " 353 " + cnick + " = " + cname + " :" + channelnames + "\r\n");
	this->messageClient(":" + this->cuser + " 366 " + cnick + " " + cname + " :End of /NAMES list.\r\n");
}

void	Client::quit()
{
	std::string	reason;
	if (arguments.size() < 1)
		reason = "";
	else
	{
		for (size_t i = 0; i < arguments.size(); i++)
		{
			reason += arguments[i];
			reason += " ";
		}
	}
	std::string quitMessage = ":" + this->getNick() + "!" + cuser + "@" + userIP + " QUIT: " + reason + "\r\n";
	std::vector<Channel*>& channels = server.getChannelList();
 	for (size_t i = 0; i < channels.size(); ++i)
	{
		Channel* ch = channels[i];
		if (ch->isAlreadyMember(this))
		{
			ch->broadcast(quitMessage, this);
			ch->removeClient(this);
			Client* remainingClient = ch->getOnlyClient();
			if (remainingClient && !ch->isOperator(remainingClient))
				ch->setOp(remainingClient);
		}
	}
	messageClient(":" + cnick + "!" + cuser + "@" + userIP + " QUIT " + reason + "\r\n");
	disconnected = true;
	return ;
}

void	Client::part()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.empty())
		return printMessage(ERR_NEED_MORE_PARAMS);
	std::string chname = arguments[0];
	std::string reason;
	if (chname[0] != '#')
		return printMessage(ERR_BAD_CHAN_MASK);
	if (!channelexist(chname))
		return printMessage(ERR_NO_SUCH_CHANNEL);
	Channel *targetchannel = NULL;
	std::vector<Channel*>& channels = server.getChannelList();
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i]->getName() == chname)
		{
			targetchannel = channels[i];
			break;
		}
	}
	if (!targetchannel || !targetchannel->isAlreadyMember(this))
		return printMessage(ERR_NOT_ON_CHANNEL);
	if (arguments.size() == 2)
		reason = arguments[1];
	std::string part_message = ":" + getFullMask() + " PART " + chname;
	if (!reason.empty())
		part_message += " :" + reason;
	part_message += "\r\n";
	targetchannel->broadcast(part_message, NULL);
	targetchannel->removeClient(this);
	if (targetchannel->getUserCount() == 1)
	{
		Client* remainingClient = targetchannel->getOnlyClient();
		if (remainingClient)
			targetchannel->setOp(remainingClient);
	}
	if (targetchannel && targetchannel->getClients().empty())
	{
		server.removeChannel(chname);
		targetchannel = NULL;
	}
	return printMessage(LEAVE_CHANNEL);
}

void	Client::ping()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.size() != 1)
		return printMessage(ERR_NEED_MORE_PARAMS);
	return printMessage(PONG);
}

void	Client::fast()
{
	authenticatedcheck = true;
	cuser = "userum";
	crealname = "nomerealum";
	cnick = "nickum";
	server.setNewcNick(cnick, "nickum");
}

void	Client::fast2()
{
	authenticatedcheck = true;
	cuser = "userdois";
	crealname = "nomerealdois";
	cnick = "nickdois";
	server.setNewcNick(cnick, "nickdois");
}

void	Client::msg()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.size() < 2)
		return printMessage(ERR_NEED_MORE_PARAMS);
	std::string	ambiguous = arguments[0];
	std::string message;
	for (size_t i = 1; i < arguments.size(); i++)
	{
		message += arguments[i];
		message += " ";
	}
	std::string truemessage = ":" + getFullMask() + " MSG " + ambiguous + ": " + message + "\r\n";
	if (ambiguous[0] == '#') // +-
	{
		if (!channelexist(ambiguous))
			return printMessage(ERR_NO_SUCH_CHANNEL);
		Channel *chacha = server.findChannel(ambiguous);
		if (!chacha->isAlreadyMember(this))
			return printMessage(ERR_USER_NOT_IN_CHANNEL);
		std::vector<Client*>& members = chacha->getClients();
		for (size_t i = 0; i < members.size(); i++)
			members[i]->messageClient(truemessage);
	}
	else
	{
		Client *clicli = server.getClientByNick(ambiguous);
		if (!clicli)
			return printMessage(ERR_NO_SUCH_NICK);
		clicli->messageClient(truemessage);
	}
}

void Client::kick()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.size() < 2)
		return printMessage(ERR_NEED_MORE_PARAMS);
	std::string channelname = arguments[0];
	std::string username = arguments[1];
	std::string message = "";
	if (arguments.size() == 3) // VER AQUI ISTO
	{
		for (size_t i = 2; i < arguments.size(); i++)
		{
			message += arguments[i];
			message += " ";
		}
	}
	if (channelname[0] != '#')
		return printMessage(ERR_BAD_CHAN_MASK);
	if (!channelexist(channelname))
		return printMessage(ERR_NO_SUCH_CHANNEL);
	if (!nickAlreadyExists(username))
		return printMessage(ERR_NO_SUCH_NICK);
	Channel *oldchan = NULL;
	std::vector<Channel*> &channels = server.getChannelList();
	for (size_t i = 0; i < channels.size(); ++i)
	{
		if (channels[i]->getName() == channelname)
		{
			oldchan = channels[i];
			break;
		}
	}
	if (!oldchan->isAlreadyMember(this))
		return printMessage(ERR_NOT_ON_CHANNEL);
	if (!oldchan->isOperator(this))
		return printMessage(ERR_CHAN_OP_PRIV_NEEDED);
	Client *target = server.getClientByNick(username);
	if (!target || !oldchan->isAlreadyMember(target))
		return printMessage(ERR_USER_NOT_IN_CHANNEL);
	std::string kick_msg = ":" + getFullMask() + " KICK " + channelname + " " + username;
	if (!message.empty())
		kick_msg += " :" + message;
	kick_msg += "\r\n";
	oldchan->broadcast(kick_msg, NULL);
	oldchan->addKickClient(target);
	oldchan->removeClient(target);
	target->printMessage(KICKED_CHANNEL);
	if (oldchan->getUserCount() == 1)
	{
		Client* remainingClient = oldchan->getOnlyClient();
		if (remainingClient && !oldchan->isOperator(remainingClient))
			oldchan->setOp(remainingClient);
	}
	if (!message.empty())
		printMessage(KICK_SOMEONE_MESSAGE);
	else
		printMessage(KICK_SOMEONE);
}

void	Client::topic()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.size() < 1)
		return printMessage(ERR_NEED_MORE_PARAMS);
	std::string chanchon = arguments[0];
	std::string message;
	if (chanchon[0] != '#')
		return printMessage(ERR_BAD_CHAN_MASK);
	if (!channelexist(chanchon))
		return printMessage(ERR_NO_SUCH_CHANNEL);
	Channel *thechan = NULL;
	std::vector<Channel*>& channels = server.getChannelList();
	for (size_t i = 0; i < channels.size(); i++)
	{
		if (channels[i]->getName() == chanchon)
		{
			thechan = channels[i];
			break;
		}
	}
	if (!thechan->isAlreadyMember(this))
		return printMessage(ERR_NOT_ON_CHANNEL);
	std::string oldTopic = thechan->getTopic();
	if (arguments.size() == 1)
	{
		if (!oldTopic.empty())
			message = "This channel topic is :" + thechan->getTopic() + "\r\n";
		else
			message = "Channel has no topic\r\n";
		return messageClient(message);
	}
	if (thechan->isTopicOpOnly())
	{
		if (!thechan->isOperator(this))
			return printMessage(ERR_NOT_OP);
	}
	std::string	newTopic;
	for (size_t i = 1; i < arguments.size(); i++)
	{
		newTopic += arguments[i];
		newTopic += " ";
	}
	thechan->setTopic(newTopic);
	message = this->getNick() + " set channel new topic to :" + thechan->getTopic() + "\r\n";
	thechan->broadcast(message, NULL);
}

void	Client::modeInvite(Channel *chanchan)
{
	if (!chanchan->isOperator(this))
		return printMessage(ERR_NOT_OP);
	chanchan->switchInvite();
	std::string message;
	if (chanchan->isInviteOnly())
	{
		chanchan->addMode('i');
		message = this->getNick() + " sets mode +i on " + chanchan->getName() + "\r\n";
	}
	else
	{
		chanchan->removeMode('i');
		message = this->getNick() + " sets mode -i on " + chanchan->getName() + "\r\n";
	}
	chanchan->broadcast(message, NULL);
}

void	Client::modeOperator(Channel *chanchan)
{
	if (arguments.size() < 3)
		return ;
	std::string nome = arguments[2];
	Client *cleinte = server.getClientByNick(nome);
	std::string meesage;
	if (!cleinte)
		return ;
	if (!chanchan->isOperator(cleinte))
	{
		meesage = this->getNick() + " gives channel operator to " + cleinte->getNick() + "\r\n";
		chanchan->broadcast(meesage, NULL);
		chanchan->setOp(cleinte);
	}
	else
	{
		meesage = this->getNick() + " removes channel operator from " + cleinte->getNick() + "\r\n";
		chanchan->broadcast(meesage, NULL);
		chanchan->removeOp(cleinte);
	}
}

// void	Client::modeTopic(Channel *chanchan)
// {
	// topic ainda nao v\e o mode
	// fazer alguma maneira facil de dar store aos modos ativos, tipo uma string com todos os modos ou algo do genreo
// }

void Client::modeChannel(Channel *chanchan)
{
	std::ostringstream oss;
	oss << chanchan->getUserLimit();
	std::string limitStr = oss.str();
	if (!chanchan->isAlreadyMember(this))
		return printMessage(ERR_NOT_ON_CHANNEL);
	std::string message;
	if (chanchan->getModes().empty())
		message = "Channel " + chanchan->getName() + " has no modes " + limitStr + chanchan->getPassword() + "\r\n";
	else	
		message = "Channel " + chanchan->getName() + " modes: " + chanchan->getModes() + " " + limitStr + chanchan->getPassword() + "\r\n";
	chanchan->broadcast(message, NULL);
}

// sem args: Channel #alphas modes: +Cnstlk <user_limit> <keyword>
// 		     Channel #alphas created on Thu Mar 19 13:59:11 2026

void Client::modeTopic(Channel *chanchan)
{
	if (!chanchan->isAlreadyMember(this))
		return printMessage(ERR_NOT_ON_CHANNEL);
	if (!chanchan->isOperator(this))
		return printMessage(ERR_NOT_OP);
	std::string message;
	chanchan->switchTopic();
	if (chanchan->isTopicOpOnly())
	{
		chanchan->addMode('t');
		message = this->getNick() + " sets mode +t on " + chanchan->getName() + "\r\n";
	}
	else
	{
		chanchan->removeMode('t');
		message = this->getNick() + " sets mode -t on " + chanchan->getName() + "\r\n";
	}
	chanchan->broadcast(message, NULL);
}

void	Client::mode()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.size() < 1)
		return printMessage(ERR_NEED_MORE_PARAMS);
	std::string chanchan = arguments[0];
	if (chanchan[0] != '#')
		return printMessage(ERR_BAD_CHAN_MASK);
	if (!channelexist(chanchan))
		return printMessage(ERR_NO_SUCH_CHANNEL);
	Channel *channel = server.findChannel(chanchan);
	if (!channel->isAlreadyMember(this))
		return printMessage(ERR_NOT_ON_CHANNEL);
	char flags = 0;
	if (arguments.size() >= 2)
		flags = arguments[1][0];
	if (!channel->isOperator(this))
		return printMessage(ERR_NOT_OP);
	switch (flags)
	{
		case 'i':
			modeInvite(channel);
			break;
		case 't':
			modeTopic(channel);
			break;
		// case 'k':
		// 	modeKeyword();
		// 	break;
		// case 'l':
		// 	modeLimit(channel);
		// 	break;
		case 'o':
			modeOperator(channel);
			break;
		default:
			modeChannel(channel);
			break;
	}
}


void Client::list()
{
	if (!getAuthenticated())
		return printMessage(ERR_NOT_AUTHENTICATED);
	if (arguments.size() < 1)
		return printMessage(ERR_NEED_MORE_PARAMS);
	std::string channelname = arguments[0];
	if (channelname[0] != '#')
		return printMessage(ERR_BAD_CHAN_MASK);
	if (!channelexist(channelname))
		return printMessage(ERR_NO_SUCH_CHANNEL);
	Channel *channel = server.findChannel(channelname);
	const std::vector<Client*>& members = channel->getClients();
	std::string message = "Members in " + channelname + ":\r\n";
	for (size_t i = 0; i < members.size(); i++)
	{
		message += "  ";
		if (channel->isOperator(members[i]))
			message += "[@] ";
		else
			message += "[ ] ";
		message += members[i]->getNick();
		message += " (" + members[i]->getFullMask() + ")";
		message += "\r\n";
	}
	messageClient(message);
}