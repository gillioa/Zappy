#include "CircularBuffer.hpp"

CircularBuffer::CircularBuffer(unsigned int size)
{
  _buf.set_capacity(size);
  _buf.resize(size);
}

void CircularBuffer::pushString(std::string const &str)
{
  std::string::const_iterator i = str.begin();

  while (i != str.end()) {
    _buf.push_back(*i);
    i++;
  }
}

bool CircularBuffer::getFirstString(std::string &msg)
{
  boost::circular_buffer<char>::iterator it;
  boost::circular_buffer<char>::iterator save;

  msg.clear();
  it = _buf.begin();
  for (it = _buf.begin(); it != _buf.end() && *it == 0; it++);
  save = it;
  while (it != _buf.end() && *it != '\n')
    {
      msg.push_back(*it);
      it++;
    }
  if (it == _buf.end())
    return (false);
  if (*it != '\n')
    return (false);
  it = save;
  while (it != _buf.end() && *it != '\n')
    {
      *it = '\0';
      it++;
    }
  *it = '\0';
  return (true);
}

unsigned int CircularBuffer::sizeEmpty() const
{
  boost::circular_buffer<char>::const_iterator it;
  unsigned int size = 0;

  for (it = _buf.begin(); it != _buf.end() && *it == 0; it++) {
    size++;
  }
  return (size);
}

bool CircularBuffer::isEmpty() const
{
  return (_buf.empty());
}

bool CircularBuffer::isFull() const
{
  return (_buf.full());
}
