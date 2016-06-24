#include "Team.hpp"

Team::Team(std::string const &str, sf::Color col) : _teamName(str), _color(col)
{

}

Team::~Team()
{
  std::list<Player *>::iterator it;
  std::list<Egg *>::iterator it2;

  for (it = _players.begin(); it != _players.end(); it++) {
    delete (*it);
  }
  for (it2 = _egg.begin(); it2 != _egg.end(); it2++) {
    delete (*it2);
  }
}

void Team::setTeamColor(sf::Color const &col)
{
  _color = col;
}

sf::Color const &Team::getTeamColor() const
{
  return (_color);
}

void Team::setNewPlayer(Player *playe)
{
  _players.push_back(playe);
}

std::list<Player*> &Team::getPlayers()
{
  return (_players);
}

std::string const &Team::getTeamName() const
{
  return (_teamName);
}

void Team::setTeamName(std::string const &str)
{
  _teamName = str;
}

std::list<Egg*> &Team::getEggs()
{
  return (_egg);
}

void Team::setNewEgg(Egg *egg)
{
  _egg.push_back(egg);
}

unsigned int Team::getMaxLevel() const
{
  unsigned int level = 0;
  for (auto &i : _players)
  {
    if (i->getLevel() > level)
      level = i->getLevel();
  }
  return level;
}