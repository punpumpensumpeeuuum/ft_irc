/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:58:33 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/30 05:15:25 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

void	Client::messageClient(std::string mes)
{
	mes += "\r\n";
	send(fd, mes.c_str(), mes.length(), 0);
}

void	Client::messageClient(int nb)
{
	std::ostringstream oss;
	oss << nb;	
	std::string mes = oss.str();
	mes += "\r\n";
	send(fd, mes.c_str(), mes.length(), 0);
}

void	Client::printMessage(int nb)
{
	std::ostringstream oss;
	// oss << ":" << "server" << " " << nb << " " << nick << " :";

	switch (nb)
	{
		case ERR_NO_SUCH_NICK:
			oss << "No such nick/channel";
			break;
		case ERR_NO_SUCH_CHANNEL:
			oss << "No such channel";
			break;
		case ERR_CANNOT_SEND_TO_CHAN:
			oss << "Cannot send to channel";
			break;
		case ERR_TOO_MANY_CHANNELS:
			oss << "Too many channels";
			break;
		case ERR_UNKNOWN_COMMAND:
			oss << "Unknown command or invalid argument";
			break;
		case ERR_NO_NICKNAME_GIVEN:
			oss << "No nickname given";
			break;
		case ERR_ERRONEUS_NICKNAME:
			oss << "Erroneous nickname";
			break;
		case ERR_NICKNAME_IN_USE:
			oss << "Nickname is already in use";
			break;
		case ERR_USER_NOT_IN_CHANNEL:
			oss << "User is not in the channel";
			break;
		case ERR_NOT_ON_CHANNEL:
			oss << "Not on channel";
			break;
		case ERR_USER_ALREADY_INVITED:
			oss << "User is already invited";
			break;
		case ERR_USER_ON_CHANNEL:
			oss << "User is already on the channel";
			break;
		case ERR_NEED_MORE_PARAMS:
			oss << "Need more parameters";
			break;
		case ERR_ALREADY_REGISTERED:
			oss << "Already registered";
			break;
		case ERR_NOT_AUTHENTICATED:
			oss << "Not authenticated";
			break;
		case ERR_PASSWD_MIS_MATCH:
			oss << "Password mismatch";
			break;
		case ERR_INVALID_PASSWORD:
			oss << "Invalid password";
			break;
		case ERR_CHANNEL_IS_FULL:
			oss << "Channel is full";
			break;
		case ERR_UNKNOWN_MODE:
			oss << "Unknown mode";
			break;
		case ERR_INVITE_ONLY_CHAN:
			oss << "Invite only channel";
			break;
		case ERR_BAD_CHANNEL_KEY:
			oss << "Bad channel key";
			break;
		case ERR_BAD_CHAN_MASK:
			oss << "Bad channel mask, channel name should start with (#)";
			break;
		case ERR_CHAN_OP_PRIV_NEEDED:
			oss << "Channel operator privileges needed";
			break;
		case ERR_NO_OPER_HOST:
			oss << "No operator host";
			break;
		case ERR_USERS_DONT_MATCH:
			oss << "Users don't match";
			break;
		case ERR_INVALID_INPUT:
			oss << "Invalid Input";
			break;
		case ERR_ERRONEUS_USER:
			oss << "Erroneous User";
			break;
		case ERR_ERRONEUS_REAL_NAME:
			oss << "Erroneous Real Name";
			break;
		case ERR_NO_MESSAGE_GIVEN:
			oss << "No message given";
			break;
		case WAIT_FOR_PASS:
			oss << "Please insert the server password";
			break;
		case WAIT_FOR_NICK:
			oss << "Please assign your nickname";
			break;		
		case WAIT_FOR_USER:
			oss << "Please assign your realname";
			break;
	}
	messageClient(oss.str());
}