//
// FileDescr.hpp for Plaza in /home/courtu_r/tests/plazza
//
// Made by courtu_r
// Login   <courtu_r@epitech.net>
//
// Started on  Fri Apr 18 13:36:56 2014 courtu_r
// Last update Fri Apr 25 15:42:38 2014 remaud_c
//

#ifndef FILEDESCR
# define FILEDESCR

#include <unistd.h>
#include <fcntl.h>

class	FileDescr
{
  int	_fd;
  fd_set	_rfds;
  struct timeval _time;
public:
  void	setTime(int sec, int usec);
  void	setFd(int fd);
  void	clearFd();
  bool	isSet(int fd) const;
  int	setNonBlock();
};

#endif /*FILEDESCR*/
