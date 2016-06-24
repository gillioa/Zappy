#ifndef CASE_HPP__

# define CASE_HPP__

#include <SFML/Graphics.hpp>
#include <mutex>

#include "Color.hpp"

enum eRessources {
  Nourriture = 0,
  Linemate,
  Deraumere,
  Sibur,
  Mendiane,
  Phiras,
  Thystame,
};

class Player;

class Case
{
public:
  Case(unsigned int = 0, unsigned int = 0);
  ~Case();
public:
  unsigned int getX() const;
  unsigned int getY() const;
  sf::RectangleShape getShape() const;
  void setX(unsigned int);
  void setY(unsigned int);
  void focusShape();
  void unFocusShape();
  void setIncantParam(bool, unsigned int, bool);
  unsigned int getIncLvl() const;
  bool getIncSucceed() const;
  bool getIncantationIsSet() const;
  void setRessources(eRessources, unsigned int);
  std::map<eRessources, unsigned int> & getRessources();
  void updateIncLevel();
  unsigned int getIncRotation() const;
private:
  bool			_incantation;
  bool			_incSucceed;
  unsigned int		_incLvl;
  unsigned int		m_x;
  unsigned int		m_y;
  sf::RectangleShape  m_shape;
  std::map<eRessources, unsigned int> _ressources;
  std::mutex m_mutex;
};

#endif /* EOF - Case.hpp */
