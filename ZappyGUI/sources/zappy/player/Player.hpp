#ifndef PLAYER_HPP__

# define PLAYER_HPP__

#include <map>
#include <mutex>

#include "Case.hpp"
#include "Socket.hpp"

enum eOrientation { NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4 };

enum eAction {
  Expulse = 0,
  Broadcast,
  IncantationLaunch,
  Fork,
  PutRessources,
  GetRessources,
  Nothing,
};

enum eStat {
  Incantation = 0,
  Not,
};

class Player
{
public:
  Player(int, unsigned int = 0, unsigned int = 0);
  ~Player();
  void setX(unsigned int);
  void setY(unsigned int);
  void setOrientation(eOrientation);
  eOrientation getOrientation() const;
  void setLevel(unsigned int);
  unsigned int getLevel() const;
  unsigned int getY() const;
  unsigned int getX() const;
  int getId() const;
  void setCurrentAction(eAction);
  eAction getCurrentAction() const;
  void setRessource(eRessources, unsigned int);
  std::map<eRessources, unsigned int> const &getRessource() const;
  void setBroadCastMsg(std::string const &);
  std::string const &getBroadCastMsg() const;
  eStat getCurrentStat() const;
  void setCurrentStat(eStat);
  void setIncantationParam(unsigned int, unsigned int, unsigned int);
  std::vector<unsigned int> const &getIncantationParam() const;
  unsigned int getBroadCastLevel() const;
  void updateBroadCastLevel();
  std::string const &getStringAction();
  void demandInventory(Socket *);
private:
  eAction _currentAction;
  std::string _strCurAction;
  std::vector<unsigned int> _incantationParam;
  eStat _currentStat;
  unsigned int m_x;
  unsigned int m_y;
  unsigned int _level;
  int m_id;
  eOrientation _orient;
  std::string _broadCastMsg;
  std::map<eRessources, unsigned int> _ressources;
  std::mutex m_mutex;
private:
  unsigned int m_broadCastLevel;
};

#endif // EOF - Player.hpp
