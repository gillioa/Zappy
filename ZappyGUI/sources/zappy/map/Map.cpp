#include <iostream>

#include "Map.hpp"

Map::Map() : m_length(0), m_width(0)
{
}

Map::Map(unsigned int l, unsigned int w) : m_length(l), m_width(w)
{
}

Map::~Map()
{
  m_map.clear();
}

Case*   Map::atCoords(unsigned int x, unsigned int y)
{
  unsigned int n = x * m_width + y;
  return m_map[n];
}

unsigned int		Map::getLength() const
{
  return m_length;
}

unsigned int		Map::getWidth() const
{
  return m_width;
}

void Map::setMap(unsigned int l, unsigned int w)
{
  m_length = l;
  m_width = w;

  _initialize_clear_map();
}

void Map::_initialize_clear_map()
{
  unsigned int x = 0;
  unsigned int y = 0;
  m_map.clear();

  for (unsigned int i = 0; i < m_width * m_length ; ++i)
  {
    m_map.push_back( new Case(x, y) );
    if (y < m_width - 1)
    {
      y += 1;
    }
    else
    {
      y = 0;
      x += 1;
    }
  }
}

std::vector<Case *> & Map::getVectCase()
{
  return m_map;
}
