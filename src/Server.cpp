#include "Server.hpp"

Server::Server() {}

Server::Server(std::string port, std::string pswd) : _port(atoi(port.c_str())), _password(pswd) {}

Server::~Server() {}

void Server::init()
{
	// AF_INET      :   IPv4 protocol
	// SOCK_STREAM  :   TCP socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	// htons(): Converts port to network byte order.
	serverAddress.sin_port = htons(8080);
	// INADDR_ANY: Accept connections on any IP.
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	std::cout << serverSocket << " | " << serverAddress.sin_port << std::endl;

	// close(serverSocket);
}
