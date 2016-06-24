#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

#include <string>
#include <boost/circular_buffer.hpp>

class CircularBuffer
{
  boost::circular_buffer<char> _buf;
public:
  CircularBuffer(unsigned int);
  ~CircularBuffer() {};
  void pushString(std::string const &);
  bool getFirstString(std::string &);
  bool isEmpty() const;
  bool isFull() const;
  unsigned int sizeEmpty() const;
};

#endif
