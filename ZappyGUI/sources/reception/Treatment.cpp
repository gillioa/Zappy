#include "Treatment.hpp"
#include <iostream>

Treatment::Treatment()
{

}

Treatment::~Treatment()
{
  std::cout << "Treatment DEstructionnnnn" << std::endl;
}

bool Treatment::getSubstr(std::string const &command, unsigned int i, std::string &res)
{
  std::size_t pos1 = 0, pos2 = 0;

  for (unsigned int nb = 0; nb < i; nb++)
    {
      pos1 = command.find(" ", pos2);
      if (pos1 == std::string::npos)
  	return (false);
      pos2 = command.find(" ", pos1 + 1);
      if (pos2 == std::string::npos)
	pos2 = command.length();
    }
  res = command.substr(pos1, pos2 - pos1);
  return (true);
}

unsigned int Treatment::StringToUInt(std::string const &str)
{
  unsigned int x;

  std::istringstream ss(str);
  ss >> x;
  return (x);
}

int Treatment::StringToInt(std::string const &str)
{
  int x;

  std::istringstream ss(str);
  ss >> x;
  return (x);
}

unsigned int Treatment::generateRandomNumber(unsigned int min, unsigned int max) const
{
  unsigned int value;
  static int i;

  if (i == 0)
    srand(time(NULL));
  i++;
  while ((value = rand() % (max + 1)) < min);
  return (value);
}

bool Treatment::doMsz(std::string const &command, Zappy &data)
{
  std::string first, second;
  unsigned int x, y;

  if (data.getIsSet() == true)
    return (false);
  if (getSubstr(command, 1, first) == false)
    return (false);
  if (getSubstr(command, 2, second) == false)
    return (false);
  x = StringToUInt(first);
  y = StringToUInt(second);
  if (x == 0 || y == 0)
    return (false);
  data.setMap(x, y);
  data.setIsSet(true);
  return (true);
}

bool Treatment::doBct(std::string const &command, Zappy &data)
{
  std::string str;
  unsigned int x, y, val, res = 0;
  Case *ca;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  x = StringToUInt(str);
  if (getSubstr(command, 2, str) == false)
    return (false);
  y = StringToUInt(str);
  if (data.getMap().getLength() < x)
    return (false);
  if (data.getMap().getWidth() < y)
    return (false);
  if ((ca = data.getMap().atCoords(x, y)) == 0)
    return (false);
  for (x = 3; x < 10; x++) {
    if (getSubstr(command, x, str) == false)
      return (false);
    val = StringToUInt(str);
    ca->setRessources(static_cast<eRessources>(res), val);
    res++;
  }
  return (true);
}

bool Treatment::doTna(std::string const &command, Zappy &data)
{
  std::string name;
  unsigned int r, g, b;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, name) == false)
    return (false);
  if (data.getTeam(name) != 0)
    return (false);
  r = generateRandomNumber(0, 255);
  g = generateRandomNumber(0, 255);
  b = generateRandomNumber(0, 255);
  while (data.compareTeamColor(r, g, b) == true)
    {
      r = generateRandomNumber(0, 255);
      g = generateRandomNumber(0, 255);
      b = generateRandomNumber(0, 255);
    }
  sf::Color col(r, g, b);
  data.setNewTeam(new Team(name, col));
  return (true);
}

bool Treatment::doPnw(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  unsigned int x, y;
  Player *player = 0;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if (data.getPlayerById(id) != 0)
    player = data.getPlayerById(id);
  if (getSubstr(command, 2, str) == false)
    return (false);
  x = StringToUInt(str);
  if (getSubstr(command, 3, str) == false)
    return (false);
  y = StringToUInt(str);
  if (data.getMap().getLength() < x)
    return (false);
  if (data.getMap().getWidth() < y)
    return (false);
  if (data.getPlayerById(id) == 0)
    player = new Player(id, x, y);
  else {
    player->setX(x);
    player->setY(y);
  }
  if (getSubstr(command, 4, str) == false)
    return (false);
  player->setOrientation(static_cast<eOrientation>(StringToInt(str)));
  if (getSubstr(command, 5, str) == false)
    return (false);
  player->setLevel(StringToUInt(str));
  if (getSubstr(command, 6, str) == false)
    return (false);
  if (data.getTeam(str) == 0)
    return (false);
  if (data.getPlayerById(id) == 0)
    data.getTeam(str)->setNewPlayer(player);
  return (true);
}

bool Treatment::doPpo(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  if (getSubstr(command, 2, str) == false)
    return (false);
  if (data.getMap().getLength() < StringToUInt(str))
    return (false);
  play->setX(StringToUInt(str));
  if (getSubstr(command, 3, str) == false)
    return (false);
  if (data.getMap().getWidth() < StringToUInt(str))
    return (false);
  play->setY(StringToUInt(str));
  if (getSubstr(command, 4, str) == false)
    return (false);
  play->setOrientation(static_cast<eOrientation>(StringToInt(str)));
  return (true);
}

bool Treatment::doPlv(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  if (getSubstr(command, 2, str) == false)
    return (false);
  play->setLevel(StringToUInt(str));
  return (true);
}

bool Treatment::doPin(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;
  unsigned int val, res = 0;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  if (getSubstr(command, 2, str) == false)
    return (false);
  if (data.getMap().getLength() < StringToUInt(str))
    return (false);
  play->setX(StringToUInt(str));
  if (getSubstr(command, 3, str) == false)
    return (false);
  if (data.getMap().getWidth() < StringToUInt(str))
    return (false);
  play->setY(StringToUInt(str));
  for (unsigned int x = 3; x < 10; x++) {
    if (getSubstr(command, x, str) == false)
      return (false);
    val = StringToUInt(str);
    play->setRessource(static_cast<eRessources>(res), val);
    res++;
  }
  return (true);
}

bool Treatment::doPex(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  play->setCurrentAction(Expulse);
  return (true);
}

bool Treatment::doPbc(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  play->setCurrentAction(Broadcast);
  if (getSubstr(command, 2, str) == false)
    return (false);
  play->setBroadCastMsg(str);
  return (true);
}

bool Treatment::doPic(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  unsigned int x, y, lvl, pos;
  Player *play;
  Case *ca;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  x = StringToUInt(str);
  if (data.getMap().getLength() < StringToUInt(str))
    return (false);
  if (getSubstr(command, 2, str) == false)
    return (false);
  y = StringToUInt(str);
  if (data.getMap().getWidth() < StringToUInt(str))
    return (false);
  if (getSubstr(command, 3, str) == false)
    return (false);
  lvl = StringToUInt(str);
  if ((ca = data.getMap().atCoords(x, y)) == 0)
    return (false);
  ca->setIncantParam(true, lvl, false);
  pos = 4;
  while (getSubstr(command, pos, str) != false)
    {
      id = StringToInt(str);
      if ((play = data.getPlayerById(id)) == 0)
	return (false);
      if (pos == 4)
	play->setCurrentAction(IncantationLaunch);
      play->setCurrentStat(Incantation);
      play->setIncantationParam(x, y, lvl);
      pos++;
    }
  return (true);
}

bool Treatment::doPie(std::string const &command, Zappy &data)
{
  std::string str;
  unsigned int x, y, suc;
  Case *ca;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  x = StringToUInt(str);
  if (data.getMap().getLength() < StringToUInt(str))
    return (false);
  if (getSubstr(command, 2, str) == false)
    return (false);
  y = StringToUInt(str);
  if (data.getMap().getWidth() < StringToUInt(str))
    return (false);
  if ((ca = data.getMap().atCoords(x, y)) == 0)
    return (false);
  if (getSubstr(command, 3, str) == false)
    return (false);
  suc = StringToUInt(str);
  if (suc == 1)
    ca->setIncantParam(false, 0, true);
  else
    ca->setIncantParam(false, 0, false);
  data.deSetIncant(x, y);
  return (true);
}

bool Treatment::doPfk(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  play->setCurrentAction(Fork);
  return (true);
}

bool Treatment::doPdr(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  play->setCurrentAction(PutRessources);
  return (true);
}

bool Treatment::doPgt(std::string const &command, Zappy &data)
{
  std::string str;
  int id;
  Player *play;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  id = StringToInt(str);
  if ((play = data.getPlayerById(id)) == 0)
    return (false);
  play->setCurrentAction(GetRessources);
  return (true);
}

bool Treatment::doPdi(std::string const &command, Zappy &data)
{
  std::string str;
  std::vector<unsigned int> param;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  data.removePlayerById(StringToInt(str));
  return (true);
}

bool Treatment::doEnw(std::string const &command, Zappy &data)
{
  std::string str;
  int eggId, playerId;
  unsigned int x, y;
  Egg *egg;
  Player *play;
  Team *team;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  eggId = StringToInt(str);
  if (data.getEggById(eggId) != 0)
    return (false);
  if (getSubstr(command, 2, str) == false)
    return (false);
  playerId = StringToInt(str);
  if ((play = data.getPlayerById(playerId)) == 0)
    return (false);
  if ((team = data.getTeamByPlayerId(playerId)) == 0)
    return (false);
  if (getSubstr(command, 3, str) == false)
    return (false);
  x = StringToUInt(str);
  if (getSubstr(command, 4, str) == false)
    return (false);
  y = StringToUInt(str);
  if (data.getMap().getLength() < x)
    return (false);
  if (data.getMap().getWidth() < y)
    return (false);
  egg = new Egg(eggId, x, y);
  team->setNewEgg(egg);
  if (play->getCurrentAction() == Fork)
    play->setCurrentAction(Nothing);
  return (true);
}

bool Treatment::doEht(std::string const &command, Zappy &data)
{
  std::string str;
  Egg *egg;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  if ((egg = data.getEggById(StringToInt(str))) == 0)
    return (false);
  egg->setStat(Eclot);
  return (true);
}

bool Treatment::doEbo(std::string const &command, Zappy &data)
{
  std::string str;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  if (data.getEggById(StringToInt(str)) == 0)
    return (false);
  data.removeEggById(StringToInt(str));
  return (true);
}

bool Treatment::doEdi(std::string const &command, Zappy &data)
{
  std::string str;

  if (data.getIsSet() == false)
    return (false);
  if (getSubstr(command, 1, str) == false)
    return (false);
  if (data.getEggById(StringToInt(str)) == 0)
    return (false);
  data.removeEggById(StringToInt(str));
  return (true);
}

bool Treatment::doSgt(std::string const &command, Zappy &data)
{
  std::string str;

  if (getSubstr(command, 1, str) == false)
    return (false);
  data.setTimeRef(StringToUInt(str));
  return (true);
}

bool Treatment::doSeg(std::string const &command, Zappy &data)
{
  std::string str;

  if (getSubstr(command, 1, str) == false)
    return (false);
  data.setEndGame(true);
  data.setWinnerTeam(str);
  return (true);
}

bool Treatment::doSmg(std::string const &command, Zappy &)
{
  std::string str;

  if (getSubstr(command, 1, str) == false)
    return (false);
  std::cout << "Server Message : " << str << std::endl;
  return (true);
}

bool Treatment::doSuc(std::string const &, Zappy &)
{
  std::cerr << "Unknown Command Send To Server From this Client" << std::endl;
  return (true);
}

bool Treatment::doSbp(std::string const &, Zappy &)
{
  std::cerr << "Command with parameter send to server from this client" << std::endl; 
  return (true);
}
