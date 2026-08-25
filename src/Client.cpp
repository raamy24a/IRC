#include "Client.hpp"

Client::Client() {}

Client::~Client() {}

void Client::setAddr(sockaddr_in address) { _addr = address; }

sockaddr_in Client::getAddr() { return (_addr); }
