#ifndef ZAPPY_HPP_
# define ZAPPY_HPP_

#include <string>
#include <mutex>

#include "Map.hpp"
#include "Team.hpp"
#include "Socket.hpp"

class Zappy
{
public:
  Zappy();
  ~Zappy();
  Map & getMap();
  void setMap(unsigned int, unsigned int);
  void restartClock();
  void setNewTeam(Team *team);
  Team *getTeam(std::string const &name) const;
  Egg *getEggById(int) const;
  Team *getTeamByPlayerId(int) const;
  Player *getPlayerById(int) const;
  void removePlayerById(int);
  void removeEggById(int);
  const std::list<Team *> & getTeam() const;
  void setIsSet(bool);
  bool getIsSet() const;
  unsigned int getTimeRef() const;
  void setTimeRef(unsigned int);
  void setEndGame(bool);
  bool getEndGame() const;
  void setWinnerTeam(std::string const &);
  std::string const &getWinnerTeam() const;
  void lock();
  void unlock();
  Team *getTeamById(unsigned int);
  void deSetIncant(unsigned int, unsigned int);
  bool compareTeamColor(unsigned int, unsigned int, unsigned int) const;
  void sendTimeToServer(unsigned int, Socket &);
private:
  bool _endGame;
  std::string _winnerTeam;
  Map m_map;
  bool _mapIsSet;
  unsigned int _timeRef;
  std::list<Team *> m_team;
  sf::Clock m_clock;
  std::mutex m_mutex;
};

#endif // ZAPPY_HPP__
