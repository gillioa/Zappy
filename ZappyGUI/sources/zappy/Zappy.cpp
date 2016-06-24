#include <iostream>
#include <sstream>
#include "Zappy.hpp"

Zappy::Zappy()
{
  _mapIsSet = false;
  _endGame = false;
  _winnerTeam = "";
}

Zappy::~Zappy()
{
  std::list<Team *>::iterator it;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    delete (*it);
  }
}

void Zappy::sendTimeToServer(unsigned int time, Socket &sock)
{
  std::ostringstream ss;

  ss << "sst " << time << std::endl;
  sock.writeOnSocket(ss.str());
}

bool Zappy::compareTeamColor(unsigned int r, unsigned int g, unsigned int b) const
{
  sf::Color test(r, g, b);
  std::list<Team *>::const_iterator it;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    if (test == (*it)->getTeamColor())
      return (true);
  }
  return (false);
}

void Zappy::deSetIncant(unsigned int x, unsigned int y)
{
  std::list<Team*>::iterator it;
  std::list<Player *>::iterator it2;
  std::vector<unsigned int> vec;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    std::list<Player*> &li = (*it)->getPlayers();
    for (it2 = li.begin(); it2 != li.end(); it2++) {
      vec = (*it2)->getIncantationParam();
      if (vec[2] != 0 && vec[0] == x && vec[1] == y) {
	(*it2)->setIncantationParam(0, 0, 0);
	if ((*it2)->getCurrentAction() == IncantationLaunch)
	  (*it2)->setCurrentAction(Nothing);
	if ((*it2)->getCurrentStat() == Incantation)
	  (*it2)->setCurrentStat(Not);
      }
    }
  }
}

void Zappy::setEndGame(bool end)
{
  _endGame = end;
}

bool Zappy::getEndGame() const
{
  return (_endGame);
}

void Zappy::setWinnerTeam(std::string const &t)
{
  _winnerTeam = t;
}

Team *Zappy::getTeamById(unsigned int id)
{
  for (auto &i : m_team)
  {
    if (id == 0)
      return i;
    --id;
  }
  return NULL;
}

std::string const &Zappy::getWinnerTeam() const
{
  return (_winnerTeam);
}

void Zappy::setTimeRef(unsigned int time)
{
  _timeRef = time;
}

unsigned int Zappy::getTimeRef() const
{
  return (_timeRef);
}

Map & Zappy::getMap()
{
  return (m_map);
}

void Zappy::setMap(unsigned int x, unsigned int y)
{
  m_map.setMap(x, y);
}


void Zappy::restartClock()
{
  m_clock.restart();
}

void Zappy::removeEggById(int id)
{
  m_mutex.lock();
  std::list<Team *>::iterator it;
  std::list<Egg *>::iterator it2;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    std::list<Egg *> &li = (*it)->getEggs();
    for (it2 = li.begin(); it2 != li.end(); it2++) {
      if ((*it2)->getId() == id)
	{
	  li.erase(it2);
	  m_mutex.unlock();
	  return ;
	}
    }
  }
  m_mutex.unlock();
}

void Zappy::removePlayerById(int id)
{
  m_mutex.lock();
  std::list<Team *>::iterator it;
  std::list<Player *>::iterator it2;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    std::list<Player *> &li = (*it)->getPlayers();
    for (it2 = li.begin(); it2 != li.end(); it2++) {
      if ((*it2)->getId() == id)
	{
	  li.erase(it2);
	  m_mutex.unlock();
	  std::cout << "Player deleted" << std::endl;
	  return ;
	}
    }
  }
  m_mutex.unlock();
}

void Zappy::setNewTeam(Team *team)
{
  m_team.push_back(team);
}

const std::list<Team *> & Zappy::getTeam() const
{
  return (m_team);
}

Team *Zappy::getTeam(std::string const &name) const
{
  std::list<Team*>::const_iterator it;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    if ((*it)->getTeamName() == name)
      return (*it);
  }
  return (0);
}

Player *Zappy::getPlayerById(int id) const
{
  std::list<Team *>::const_iterator it;
  std::list<Player *> li;
  std::list<Player *>::const_iterator it2;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    li = (*it)->getPlayers();
    for (it2 = li.begin(); it2 != li.end(); it2++) {
      if ((*it2)->getId() == id)
	return (*it2);
    }
  }
  return (0);
}

void Zappy::setIsSet(bool s)
{
  _mapIsSet = s;
}

bool Zappy::getIsSet() const
{
  return (_mapIsSet);
}

Egg *Zappy::getEggById(int id) const
{
  std::list<Team *>::const_iterator it;
  std::list<Egg *> li;
  std::list<Egg *>::const_iterator it2;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    li = (*it)->getEggs();
    for (it2 = li.begin(); it2 != li.end(); it2++) {
      if ((*it2)->getId() == id)
	return (*it2);
    }
  }
  return (0);
}

Team *Zappy::getTeamByPlayerId(int id) const
{
  std::list<Team *>::const_iterator it;
  std::list<Player *> li;
  std::list<Player *>::const_iterator it2;

  for (it = m_team.begin(); it != m_team.end(); it++) {
    li = (*it)->getPlayers();
    for (it2 = li.begin(); it2 != li.end(); it2++) {
      if ((*it2)->getId() == id)
	return (*it);
    }
  }
  return (0);
}

void Zappy::lock()
{
  m_mutex.lock();
}

void Zappy::unlock()
{
  m_mutex.unlock();
}
