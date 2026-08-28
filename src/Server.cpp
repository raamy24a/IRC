#include "Server.hpp"

Server::Server() {}

Server::Server(std::string port, std::string pswd) : _port(atoi(port.c_str())), _password(pswd) {}

Server::~Server() {}

void Server::init()
{
	// AF_INET      :   IPv4 protocol
	// SOCK_STREAM  :   TCP socket
	// -Server FD-
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
		throw std::runtime_error("Error: Failed socket()");

	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Error: Failed setsockopt()");

	// sockaddr_in: It is the data type that is used to store the address of the socket.
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	// htons(): Converts port to network byte order.
	serverAddress.sin_port = htons(_port);
	// INADDR_ANY: Accept connections on any IP.
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
		throw std::runtime_error("Error: Failed bind()");

	if (listen(serverSocket, 128) == -1)
		throw std::runtime_error("Error: Failed listen()");

	int epFd = epoll_create1(0); // 0 or EPOLL_CLOEXEC
	if (epFd == -1)
		throw std::runtime_error("Error: Failed epoll_create1()");

	epoll_event epev;
	epev.events = EPOLLIN; // or EPPOLLRDHUP
	epev.data.fd = serverSocket;
	if (epoll_ctl(epFd, EPOLL_CTL_ADD, serverSocket, &epev) == -1)
		throw std::runtime_error("Error: Failed epoll_ctl()");

	epoll_event events[10];
	while (1)
	{
		int fds = epoll_wait(epFd, events, 10, -1);

		for (int i = 0; i < fds; i++)
		{
			// -FD in use-
			int fdUsed = events[i].data.fd;
			if (fdUsed == serverSocket)
			{
				sockaddr_in clientAddr;
				socklen_t clientAddrLen = sizeof(clientAddr);

				// New connection
				// -Client FD-
				int clientSocket = accept(serverSocket, (sockaddr *)&clientAddr, &clientAddrLen);
				if (clientSocket == -1)
					throw std::runtime_error("Error: Failed accept()");

				// Event IN from new connection
				epoll_event clientEvent;
				clientEvent.events = EPOLLIN;
				clientEvent.data.fd = clientSocket;
				if (epoll_ctl(epFd, EPOLL_CTL_ADD, clientSocket, &clientEvent) == -1)
					throw std::runtime_error("Error: Failed client epoll_ctl() ADD");

				std::cout << "Client " << clientSocket << " connected." << std::endl;

				Client newClient;
				newClient.setAddr(clientAddr);
				_clients[clientSocket] = newClient;
			}
			else
			{
				_clients[fdUsed].setFd(fdUsed);
				char buffer[1024];
				ssize_t bytes = recv(fdUsed, buffer, sizeof(buffer) - 1, 0);
				if (bytes == 0)
				{
					std::cout << "Client " << fdUsed << " disconnected." << std::endl;
					epoll_ctl(serverSocket, EPOLL_CTL_DEL, fdUsed, NULL);
					close(fdUsed);
				}
				else if (bytes < 0)
				{
					throw std::runtime_error("Error: Couldn't read from client.");
					epoll_ctl(serverSocket, EPOLL_CTL_DEL, fdUsed, NULL);
					close(fdUsed);
				}
				else
				{
					buffer[bytes - 1] = '\0';
					readCommand(fdUsed, buffer);
				}
			}
		}
	}

	close(epFd);
	close(serverSocket);
}

void Server::readCommand(int fd, std::string buffer)
{
	if (buffer.empty())
		return;

	Client &user = _clients[fd];

	if (_clients[fd].isInChan())
	{
		// If is a cmd
		if (buffer.at(0) == '/')
		{
			splitTokens(fd, buffer);
			handleCmds(user);
			removeTokens(fd);
		}
		else
		{
			// Concatenate Nickname with client's msg
			std::string buff = user.getNick() + " : " + buffer + '\n';

			std::map<int, Client>::iterator it;
			for (it = _clients.begin(); it != _clients.end(); it++)
			{
				if (_clients[it->first].isInChan() && fd != it->first && _clients[it->first].getChan() == _clients[fd].getChan())
				{
					ssize_t bytes = send(it->first, buff.c_str(), buff.size(), 0);
					if (bytes == 0)
						throw std::runtime_error("Error: <In channel> Client disconnected ?");
					else if (bytes < 0)
						throw std::runtime_error("Error: <In channel> Couldn't read from client.");
				}
			}
			std::cout << "Client " << fd << " on channel <" << _clients[fd].getChan() << "> : " << buff;
		}
	}
	else
	{
		// If is a cmd
		if (buffer.at(0) == '/')
		{
			splitTokens(fd, buffer);
			handleCmds(user);
			removeTokens(fd);
		}
	}
}

void Server::handleCmds(Client user)
{
	std::string cmd = user.getToken()[0].substr(1, user.getToken()[0].size());
	if (cmd == "join")
		joinChan(user);
	else if (cmd == "msg")
		msgClient(user);
	else if (cmd == "nick")
		changeNick(user);
	else
	{
		std::string str = "<" + cmd + ">" + " :Unknown command\n";
		send(user.getFd(), str.c_str(), str.size(), 0);
	}
}

void Server::changeNick(Client user)
{
	std::vector<std::string> tokens = user.getToken();

	if (tokens.size() != 2)
		send(user.getFd(), "<nick> :No nickname given.\n", 28, 0);
	else
	{
		std::map<int, Client>::iterator it;
		for (it = _clients.begin(); it != _clients.end(); it++)
		{
			if (_clients[it->first].getNick() == tokens.at(1))
			{
				if (it->first == user.getFd())
					send(user.getFd(), "<nick> :Nickname in use is the same\n", 37, 0);
				else
					send(user.getFd(), "<nick> :Nickname is already in use\n", 36, 0);
				break;
			}
		}
		if (it == _clients.end())
			_clients[user.getFd()].setNick(tokens.at(1));
	}
}

void Server::msgClient(Client user)
{
	std::vector<std::string> tokens = user.getToken();

	if (tokens.size() != 3)
		send(user.getFd(), "Error: Wrong /msg syntax.\n", 27, 0);
	else
	{
		int targetFd = atoi(tokens.at(1).c_str());
		std::string msg = tokens.at(2) + '\n';
		if (_clients.count(targetFd) && user.getFd() != targetFd)
			send(targetFd, msg.c_str(), msg.size(), 0);
	}
}

void Server::joinChan(Client user)
{
	std::vector<std::string> tokens = user.getToken();

	if (tokens.size() != 2)
		send(user.getFd(), "Error: Wrong /join syntax.\n", 28, 0);
	else if (tokens.at(1).at(0) == '#' && tokens.at(1).at(1))
		_clients[user.getFd()].setChan(true, tokens.at(1).substr(1, tokens.at(1).size() - 1));
	else if (tokens.at(1).at(0) != '#')
		send(user.getFd(), "Error: Failed /join\nMissing '#' before channel name.\n", 54, 0);
}

void Server::removeTokens(int fd)
{
	while (_clients[fd].getToken().size())
		_clients[fd].getToken().pop_back();
}

void Server::splitTokens(int fd, std::string buffer)
{
	std::stringstream ss(buffer);
	std::string token;

	while (getline(ss, token, ' '))
		if (!token.empty())
			_clients[fd].setToken(token);
}
