#include "Socket.hpp"
#include <iostream>
#include <sstream>

Socket::Socket(std::string const &proto)
  : _protocol(proto)
{
  _gereFd.setTime(0, 0);
}

Socket::~Socket() {
}

void Socket::initSocket(std::string const &ip, std::string const &port)
{
  std::istringstream ss(port);
  ss >> _port;
  _ipAdress = ip;
  if ((_proto = getprotobyname(_protocol.c_str())) == 0)
    throw Except("Error : unknown protocol\n");
  if ((_fdSocket = socket(AF_INET, SOCK_STREAM, _proto->p_proto)) == -1)
    throw Except("Error : impossible to create socket\n");
  _sin.sin_family = AF_INET;
  _sin.sin_port = htons(_port);
  _sin.sin_addr.s_addr = inet_addr(_ipAdress.c_str());
}

void Socket::Connection() const
{
  if ((connect(_fdSocket, reinterpret_cast<struct sockaddr *>(const_cast<sockaddr_in *>(&_sin)), sizeof(_sin))) == -1)
    throw Except("Error : impossible to connect to the server\n");
}

void Socket::writeOnSocket(std::string const &msg)
{
  if (send(_fdSocket, msg.c_str(), msg.length(), 0) == -1)
    throw Except("Error : impossible to write on socket\n");
}

std::string const & Socket::readOnSocket(unsigned int size)
{
  _msgRead.clear();
  _gereFd.setTime(0, 0);
  _gereFd.setFd(_fdSocket);
  if (_gereFd.setNonBlock() == -1)
    std::cout << "Ya une couille" << std::endl;
  if (_gereFd.isSet(_fdSocket) == true)
    {
      char value[size + 1];
      for (unsigned int i = 0; i < size + 1; i++)
	value[i] = 0;
      if (read(_fdSocket, value, size) == -1)
	throw Except("Error : impossible to read on socket\n");
      _msgRead = value;
    }
  return (_msgRead);
}
