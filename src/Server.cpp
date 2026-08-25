#include "Server.hpp"

Server::Server() {}

Server::Server(std::string port, std::string pswd) : _port(atoi(port.c_str())), _password(pswd) {}

Server::~Server() {}

void Server::init()
{
	// AF_INET      :   IPv4 protocol
	// SOCK_STREAM  :   TCP socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	// sockaddr_in: It is the data type that is used to store the address of the socket.
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	// htons(): Converts port to network byte order.
	serverAddress.sin_port = htons(_port);
	// INADDR_ANY: Accept connections on any IP.
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

	listen(serverSocket, 5);

	int clientSocket = accept(serverSocket, NULL, NULL);

	char buffer[1020] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);

	std::cout << "Client : " << buffer << std::endl;

	close(serverSocket);
}
