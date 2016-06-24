#include "Player.hpp"
#include "Settings.hpp"
#include <sstream>

Player::Player(int id, unsigned int x, unsigned int y):
m_x(x),
m_y(y),
m_id(id),
m_broadCastLevel(0)
{
  _level = 0;
  _ressources[Nourriture] = 0;
  _ressources[Linemate] = 0;
  _ressources[Deraumere] = 0;
  _ressources[Sibur] = 0;
  _ressources[Mendiane] = 0;
  _ressources[Phiras] = 0;
  _ressources[Thystame] = 0;
  _currentAction = Nothing;
  _broadCastMsg = "";
  _incantationParam.push_back(0);
  _incantationParam.push_back(0);
  _incantationParam.push_back(0);
  _currentStat = Not;
}

Player::~Player()
{

}

std::string const &Player::getStringAction()
{
  if (_currentAction == Nothing)
    _strCurAction = "Nothing";
  else if (_currentAction == Expulse)
    _strCurAction = "Expulse";
  else if (_currentAction == Broadcast)
    _strCurAction = "Broadcast";
  else if (_currentAction == IncantationLaunch)
    _strCurAction = "Launch Incantation";
  else if (_currentAction == Fork)
    _strCurAction = "Fork";
  else if (_currentAction == PutRessources)
    _strCurAction = "Put a ressource";
  else if (_currentAction == GetRessources)
    _strCurAction = "Get a ressource";
  return _strCurAction;
}

void Player::demandInventory(Socket *sock)
{
  std::string str;
  std::ostringstream os;

  str = "pin ";
  os << m_id;
  str += os.str();
  str += "\n";
  sock->writeOnSocket(str);
}

void Player::setIncantationParam(unsigned int x, unsigned int y, unsigned int lvl)
{
  _incantationParam[0] = x;
  _incantationParam[1] = y;
  _incantationParam[2] = lvl;
}

unsigned int Player::getBroadCastLevel() const
{
  return m_broadCastLevel;
}

void Player::updateBroadCastLevel()
{
  if (_currentAction != Broadcast)
  {
    m_broadCastLevel = 0;
    return;
  }
  if (m_broadCastLevel > Settings::SizeBroadCast)
    m_broadCastLevel = 0;
  else
    m_broadCastLevel += Settings::SpeedBroadcast;
}

std::vector<unsigned int> const &Player::getIncantationParam() const
{
  return (_incantationParam);
}

eStat Player::getCurrentStat() const
{
  return (_currentStat);
}

void Player::setCurrentStat(eStat st)
{
  _currentStat = st;
}

void Player::setBroadCastMsg(std::string const &str)
{
  _broadCastMsg = str;
}

std::string const &Player::getBroadCastMsg() const
{
  return (_broadCastMsg);
}

void Player::setCurrentAction(eAction cur)
{
  _currentAction = cur;
}

eAction Player::getCurrentAction() const
{
  return (_currentAction);
}

void Player::setLevel(unsigned int level)
{
  _level = level;
}

void Player::setOrientation(eOrientation o)
{
  _orient = o;
}

eOrientation Player::getOrientation() const
{
  return (_orient);
}

unsigned int Player::getLevel() const
{
  return (_level);
}

void Player::setX(unsigned int x)
{
  m_x = x;
}

void Player::setY(unsigned int y)
{
  m_y = y;
}

unsigned int Player::getX() const
{
  return (m_x);
}

unsigned int Player::getY() const
{
  return (m_y);
}

int Player::getId() const
{
  return (m_id);
}

void Player::setRessource(eRessources res, unsigned int nbr)
{
  _ressources[res] = nbr;
}

std::map<eRessources, unsigned int> const &Player::getRessource() const
{
  return (_ressources);
}
