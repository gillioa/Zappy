#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <SFML/Graphics.hpp>
#include <list>
#include <mutex>
#include "Player.hpp"
#include "Egg.hpp"

class Team
{
  std::list<Player *> _players;
  std::string _teamName;
  std::list<Egg *> _egg;
  std::mutex m_mutex;
  sf::Color _color;
  //color
public:
  Team() {};
  Team(std::string const &, sf::Color);
  ~Team();
  std::list<Player *> &getPlayers();
  std::string const &getTeamName() const;
  void setTeamName(std::string const &);
  sf::Color const &getTeamColor() const;
  void setTeamColor(sf::Color const &);
  void setNewPlayer(Player *);
  void setNewEgg(Egg *);
  unsigned int getMaxLevel() const;
  std::list<Egg*> &getEggs();
};

#endif
