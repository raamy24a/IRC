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
					throw std::runtime_error("Error: Failed client epoll_ctl()");

				std::cout << "Client " << clientSocket << " connected." << std::endl;

				Client newClient;
				newClient.setAddr(clientAddr);
				_clients[clientSocket] = newClient;
			}
			else
			{
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
					std::cout << "Client " << fdUsed << " : " << buffer << std::endl;
					// std::cout << _clients[fdUsed].getAddr().sin_addr.s_addr << std::endl;
					// std::cout.write(buffer, bytes) << std::endl;
				}
			}
		}
	}

	close(epFd);
	close(serverSocket);
}
