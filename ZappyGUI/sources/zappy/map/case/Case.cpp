#include <iostream>
#include <string>

#include "Case.hpp"
#include "Player.hpp"
#include "Settings.hpp"
#include "Color.hpp"

Case::Case(unsigned int nx, unsigned int ny):
m_x(nx),
m_y(ny)
{
  int shapeSize = 25;
  
  m_shape.setSize(sf::Vector2f(shapeSize,shapeSize));
  m_shape.setPosition(m_x * shapeSize + (3 * m_x) , m_y * shapeSize + (3 * m_y));
  m_shape.setFillColor(Color::Case);
  _ressources[Nourriture] = 0;
  _ressources[Linemate] = 0;
  _ressources[Deraumere] = 0;
  _ressources[Sibur] = 0;
  _ressources[Mendiane] = 0;
  _ressources[Phiras] = 0;
  _ressources[Thystame] = 0;
  _incantation = false;
  _incLvl = 0;
  _incSucceed = false;
}

Case::~Case() { }

unsigned int Case::getX() const { return m_x; }
unsigned int Case::getY() const { return m_y; }
sf::RectangleShape Case::getShape() const { return m_shape; }

void Case::setX(unsigned int x) {   m_x = x;  }
void Case::setY(unsigned int y) {   m_y = y;  }

bool Case::getIncSucceed() const
{
  return (_incSucceed);
}

void Case::setIncantParam(bool is, unsigned int lvl, bool suc)
{
  _incantation = is;
  _incLvl = lvl;
  _incSucceed = suc;
}

bool Case::getIncantationIsSet() const
{
  return (_incantation);
}

unsigned int Case::getIncLvl() const
{
  return (_incLvl);
}

void Case::focusShape()
{
  m_shape.setFillColor(Color::CaseFocus);
}

void Case::unFocusShape()
{
  m_shape.setFillColor(Color::Case);
}

void Case::setRessources(eRessources res, unsigned int nbr)
{
  _ressources[res] = nbr;
}

std::map<eRessources, unsigned int> & Case::getRessources()
{
  return _ressources;
}

void Case::updateIncLevel()
{
  if (_incLvl > Settings::RotationMaxIncantation)
    _incLvl = 0;
  else
    _incLvl += Settings::SpeedIncantation;
}

unsigned int Case::getIncRotation() const
{
  return _incLvl;
}