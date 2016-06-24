#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "Socket.hpp"
#include "CircularBuffer.hpp"
#include "Treatment.hpp"

class Reception
{
  typedef bool (Treatment::*func)(std::string const &, Zappy &);
  std::vector<std::string> _commandList;
  func _tabCommand[24];
  Treatment _treat;
  Socket _comm;
  CircularBuffer _buf;
  Zappy &_data;
  bool verifyData(std::string const &);
  void setCmdList();
  void setFuncPointer();
public:
  Reception(Socket &, Zappy &);
  ~Reception();
  void launch();
  static void threadLaunch(Reception *);
};

#endif
