/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buddy2 <buddy2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 03:39:44 by buddy2            #+#    #+#             */
/*   Updated: 2026/01/27 06:18:54 by buddy2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.hpp"

bool	Server::signal = true;

void	Server::cmdlistInit(std::vector<std::string>& cmdl)
{
	cmdl.push_back("JOIN");
	cmdl.push_back("INVITE");
	cmdl.push_back("USER");
	cmdl.push_back("NICK");
}

Server::Server()
{
	this->serverSocket = -1;
	cmdlistInit(cmdlist);
}

Server::Server(int pooort, const std::string paaasss)
{
	this->serverSocket = -1;
	port = pooort;
	pass = paaasss;
	cmdlistInit(cmdlist);
}

Server::Server(const Server &other)
{
	(void)other;
}

Server &Server::operator=(const Server &other)
{
	(void)other;
	return (*this);
}

Server::~Server()
{
	CloseServer();
}

void	Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << "SIGNAL" << std::endl;
	Server::signal = false;
	
}

Client*	Server::getClientByFd(int fd)
{

	for (size_t i = 0; i < clientlist.size(); i++)
	{
		if (clientlist[i].getFd() == fd)
			return (&clientlist[i]);
	}
	return (NULL);
}

void	Server::CloseServer()
{
	std::cout << "Closing Server" << std::endl;
	for (size_t i = 0; i < clientlist.size(); i++)
	{
		int fd = clientlist[i].getFd();
		if (fd > 0)
			close(fd);
	}
	if (serverSocket != -1)
	{
		close(serverSocket);
		serverSocket = -1;
	}
}

void Server::CloseClient(int fd)
{
	for (size_t i = 0; i < fds.size(); i++)
	{
		if (fds[i].fd == fd)
		{
			fds.erase(fds.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < clientlist.size(); i++)
	{
		if (clientlist[i].getFd() == fd)
		{
			clientlist.erase(clientlist.begin() + i);
			break;
		}
	}
}

void	Server::Init()
{
	this->port = 5555;
	struct sockaddr_in add;
	struct pollfd NewPoll;
	add.sin_family = AF_INET;
	add.sin_port = htons(this->port);
	add.sin_addr.s_addr = INADDR_ANY;

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
		throw(std::runtime_error("faild to create socket"));
	int en = 1;
	if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(serverSocket, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("faild to bind socket"));
	if (listen(serverSocket, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() faild"));
	NewPoll.fd = serverSocket;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);

	std::cout <<  "Server <" << serverSocket << "> Connected" <<  std::endl;
	std::cout << "Waiting to accept a connection...\n";

	while (Server::signal)
	{
		if((poll(&fds[0],fds.size(),-1) == -1))
		{
			if (!Server::signal)
    		    break; 
			throw(std::runtime_error("poll() faild"));
		}
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == serverSocket)
					AcceptClient();
				else
					ReceiveData(fds[i].fd);
			}
		}
		
	}
}

void	Server::AcceptClient()
{
	Client cli;
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cliadd);

	int incofd = accept(serverSocket, (sockaddr *)&(cliadd), &len);
	if (incofd == -1)
		{std::cout << "accept() failed" << std::endl; return;}
	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	
	cli.setFd(incofd);
	cli.setIp(inet_ntoa((cliadd.sin_addr)));
	clientlist.push_back(cli);
	fds.push_back(NewPoll);

	std::cout << "Client <" << incofd << "> Connected" << std::endl;
}

void	Server::ReceiveData(int fd)
{
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	ssize_t bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes <= 0)
	{
		CloseClient(fd);
		return;
	}
	Client* cli = getClientByFd(fd);
	if (!cli)
		return;
	cli->appendMessage(std::string(buffer, bytes));
	while (cli->hasLine())
	{
		std::string cmd = cli->takeCmd();
		if (cmd.empty())
			continue;
		handlecmd(cmd, *cli);
	}
}


void	Server::handlecmd(std::string c, Client& cli)
{
	size_t i;
	if (c.size() < 1)
		return ;
	for (i = 0; i < cmdlist.size(); i++)
	{
		if (cmdlist[i] == c)
			break;
	}
	if (i >= cmdlist.size()) 
	{
		std::cout << "Command not found >" << c << std::endl;
		return;
	}
	switch (i)
	{
	case 0: 
		cli.join();
		break;
	default:
		break;
	}
}