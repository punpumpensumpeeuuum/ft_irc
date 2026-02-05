/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:58:33 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/05 19:02:17 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/client.hpp"

void	Client::messageClient(std::string mes)
{
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
			oss << "No such nick/channel\r\n";
			break;
		case ERR_NO_SUCH_CHANNEL:
			oss << "No such channel\r\n";
			break;
		case ERR_CANNOT_SEND_TO_CHAN:
			oss << "Cannot send to channel\r\n";
			break;
		case ERR_TOO_MANY_CHANNELS:
			oss << "Too many channels\r\n";
			break;
		case ERR_UNKNOWN_COMMAND:
			oss << "Unknown command or invalid argument\r\n";
			break;
		case ERR_NO_NICKNAME_GIVEN:
			oss << "No nickname given\r\n";
			break;
		case ERR_ERRONEUS_NICKNAME:
			oss << "Erroneous nickname\r\n";
			break;
		case ERR_NICKNAME_IN_USE:
			oss << "Nickname is already in use\r\n";
			break;
		case ERR_USER_NOT_IN_CHANNEL:
			oss << "User is not in the channel\r\n";
			break;
		case ERR_NOT_ON_CHANNEL:
			oss << "Not on channel\r\n";
			break;
		case ERR_USER_ALREADY_INVITED:
			oss << "User is already invited\r\n";
			break;
		case ERR_USER_ON_CHANNEL:
			oss << "User is already on the channel\r\n";
			break;
		case ERR_NEED_MORE_PARAMS:
			oss << "Need more parameters\r\n";
			break;
		case ERR_ALREADY_REGISTERED:
			oss << "Already registered\r\n";
			break;
		case ERR_NOT_AUTHENTICATED:
			oss << "Not authenticated\r\n";
			break;
		case ERR_PASSWD_MIS_MATCH:
			oss << "Password mismatch\r\n";
			break;
		case ERR_INVALID_PASSWORD:
			oss << "Invalid password\r\n";
			break;
		case ERR_CHANNEL_IS_FULL:
			oss << "Channel is full\r\n";
			break;
		case ERR_UNKNOWN_MODE:
			oss << "Unknown mode\r\n";
			break;
		case ERR_INVITE_ONLY_CHAN:
			oss << "Invite only channel\r\n";
			break;
		case ERR_BAD_CHANNEL_KEY:
			oss << "Bad channel key\r\n";
			break;
		case ERR_BAD_CHAN_MASK:
			oss << "Bad channel mask, channel name should start with (#)\r\n";
			break;
		case ERR_CHAN_OP_PRIV_NEEDED:
			oss << "Channel operator privileges needed\r\n";
			break;
		case ERR_NO_OPER_HOST:
			oss << "No operator host\r\n";
			break;
		case ERR_USERS_DONT_MATCH:
			oss << "Users don't match\r\n";
			break;
		case ERR_INVALID_INPUT:
			oss << "Invalid Input\r\n";
			break;
		case ERR_ERRONEUS_USER:
			oss << "Erroneous User\r\n";
			break;
		case ERR_ERRONEUS_REAL_NAME:
			oss << "Erroneous Real Name\r\n";
			break;
		case ERR_NO_MESSAGE_GIVEN:
			oss << "No message given\r\n";
			break;
		case PASSWORD_SUCCESS:
			oss << "001: Correct Password\r\n";
			break;
		case NICKNAME_SUCCESS:
			oss << "001: Nickname assigned: " << cnick << "\r\n";
			break;
		case USERNAME_SUCCESS:
			oss << "001: Username assigned: " << cuser << "\n";
			oss << "001: Real name assigned: " << crealname << "\r\n";
			break;
		case LOGIN_SUCCESS:
			oss << "001: Login successful welcome to the server: " << crealname << "\r\n";
			break;
		case CHANNEL_CREATED:
			oss << "Channel created: " << arguments[0] << "\r\n";
			break;
		case JOINED_CHANNEL:
			oss << "You just joined a channel: " << arguments[0] << "\r\n";
			break;
		case CHANNEL_OP:
			oss << "You just became a channel OP: " << arguments[0] << "\r\n";
			break;
		case LEAVE_CHANNEL:
			oss << "You left the channel: " << arguments[0] << "\r\n";
			break;
		case SHOWING_CHANNEL_TOPIC:
			oss << " You are seeing the topic of the channel: " << arguments[0] << "\r\n";
			break;
		case CHANNEL_TOPIC_CHANGED:
			oss << "You are changing the topic of the channel: " << arguments[0] << "\n";
			oss << "Now it is: " << arguments[1] << "\r\n";
			break;
		case KICK_SOMEONE:
			oss << "You just kicked: " << arguments[1] << "\n";
			oss << "He is no longer on channel: " << arguments[0] << "\r\n";
			break;
		case KICK_SOMEONE_MESSAGE:
			oss << "You just kicked: " << arguments[1] << "\n";
			oss << "He is no longer on channel: " << arguments[0] << "\n";
			oss << "Kick message: " << arguments[2] << "\r\n";
			break;
		case INVITE_SUCCESS:
			oss << "You invited " << arguments[0] << " to channel: " << arguments[1] << "\r\n";
			break;
		case YOU_WERE_INVITED:
			oss << "You were invited by " << arguments[0] << " to join channel: " << arguments[1] << "\r\n";
			break;
		case MODE_UPDATED:
			oss << "Channel mode updated: " << arguments[0] << " → " << arguments[1] << "\r\n";
			break;
		case PONG:
			oss << "PONG: " + arguments[0] + "\r\n";
	}
	messageClient(oss.str());
}