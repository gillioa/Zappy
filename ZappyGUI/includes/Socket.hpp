#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <string>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "FileDescr.hpp"
#include "Except.hpp"

class Socket
{
  std::string _ipAdress;
  int _port;
  std::string _protocol;
  struct protoent *_proto;
  int _fdSocket;
  struct sockaddr_in _sin;
  std::string _msgRead;
  FileDescr _gereFd;
public:
  Socket(std::string const &);
  ~Socket();
  void initSocket(std::string const &, std::string const &);
  void Connection() const;
  void writeOnSocket(std::string const &);
  std::string const & readOnSocket(unsigned int);
};

#endif
