#ifndef EXCEPT_HPP_
#define EXCEPT_HPP_

#include <stdexcept>
#include <iostream>

class Except : public std::exception
{
  std::string error;
public:
  Except(std::string const &str)
  {
    error = str;
  }
  ~Except() throw() {};
  const char * what() const throw() {
    return (error.c_str());
  }
};

#endif
