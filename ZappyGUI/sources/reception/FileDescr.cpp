#include "FileDescr.hpp"

void	FileDescr::setTime(int sec, int usec)
{
  _time.tv_sec = sec;
  _time.tv_usec = usec;
}

void	FileDescr::setFd(int fd)
{
  FD_ZERO(&(_rfds));
  _fd = fd;
  FD_SET(_fd, &(_rfds));
}

void	FileDescr::clearFd()
{
  FD_ZERO(&(_rfds));
}

bool	FileDescr::isSet(int fd) const
{
  if (FD_ISSET(fd, &_rfds))
    return (true);
  else
    return (false);
}

int	FileDescr::setNonBlock()
{
  int ret;

  ret = select(_fd + 1, &_rfds, NULL, NULL, &_time);
  if (ret == -1)
    return (ret);
  return (ret);
}
