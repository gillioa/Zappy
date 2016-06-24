#ifndef MAP_HPP_
# define MAP_HPP_

#include <algorithm>
#include <vector>
#include <mutex>
#include "Case.hpp"

class Map
{
public:
  Map();
  Map(unsigned int, unsigned int);
  ~Map();
  Case * atCoords(unsigned int, unsigned int);
  std::vector<Case *> & getVectCase();
  unsigned int getLength() const;
  unsigned int getWidth() const;
  void setMap(unsigned int, unsigned int);
private:
  std::vector<Case *> m_map;
  unsigned int    m_length;
  unsigned int    m_width;
  std::mutex m_mutex;
  void _initialize_clear_map();
};

#endif
