/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:58:33 by buddy2            #+#    #+#             */
/*   Updated: 2026/02/02 23:17:05 by buddy2           ###   ########.fr       */
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
		case PASSWORD_SUCCESS:
			oss << "001: Correct Password";
			break;
		case NICKNAME_SUCCESS:
			oss << "001: Nickname assigned: " << cnick;
			break;
		case USERNAME_SUCCESS:
			oss << "001: Username assigned: " << cuser << "\n";
			oss << "001: Real name assigned: " << crealname;
			break;
		case LOGIN_SUCCESS:
			oss << "001: Login successful welcome to the server: " << crealname;
			break;
		case CHANNEL_CREATED:
			oss << "Channel created: " << arguments[0];
			break;
		case JOINED_CHANNEL:
			oss << "You just joined a channel: " << arguments[0];
			break;
		case CHANNEL_OP:
			oss << "You just became a channel OP: " << arguments[0];
			break;
		case LEAVE_CHANNEL:
			oss << "You left the channel: " << arguments[0];
			break;
		case SHOWING_CHANNEL_TOPIC:
			oss << " You are seeing the topic of the channel: " << arguments[0];
			break;
		case CHANNEL_TOPIC_CHANGED:
			oss << "You are changing the topic of the channel: " << arguments[0] << "\n";
			oss << "Now it is: " << arguments[1];
			break;
		case KICK_SOMEONE:
			oss << "You just kicked: " << arguments[1] << "\n";
			oss << "He is no longer on channel: " << arguments[0];
			break;
		case KICK_SOMEONE_MESSAGE:
			oss << "You just kicked: " << arguments[1] << "\n";
			oss << "He is no longer on channel: " << arguments[0] << "\n";
			oss << "Kick message: " << arguments[2];
			break;
		case INVITE_SUCCESS:
			oss << "You invited " << arguments[0] << " to channel: " << arguments[1];
			break;
		case YOU_WERE_INVITED:
			oss << "You were invited by " << arguments[0] << " to join channel: " << arguments[1];
			break;
		case MODE_UPDATED:
			oss << "Channel mode updated: " << arguments[0] << " → " << arguments[1];
			break;
	}
	messageClient(oss.str());
}