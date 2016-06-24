#include "Egg.hpp"

Egg::Egg(int id, unsigned int x, unsigned int y) : _posX(x), _posY(y), _id(id)
{

}

Egg::~Egg()
{

}

void Egg::setX(unsigned int x)
{
  _posX = x;
}

void Egg::setY(unsigned int y)
{
  _posY = y;
}

unsigned int Egg::getX() const
{
  return (_posX);
}

unsigned int Egg::getY() const
{
  return (_posY);
}

int Egg::getId() const
{
  return (_id);
}

eEggStat Egg::getStat() const
{
  return (_stat);
}

void Egg::setStat(eEggStat st)
{
  _stat = st;
}
