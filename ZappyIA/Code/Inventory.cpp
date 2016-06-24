
#include "Inventory.hpp"

Inventory::Inventory() {
  this->food = 0;
  this->linemate = 0;
  this->deraumere = 0;
  this->sibur = 0;
  this->mendiane = 0;
  this->phiras = 0;
  this->thystame = 0;
  this->player = 0;
}

Inventory::Inventory(std::string & s) {
  this->food = 0;
  this->linemate = 0;
  this->deraumere = 0;
  this->sibur = 0;
  this->mendiane = 0;
  this->phiras = 0;
  this->thystame = 0;
  this->player = 0;
  addSawCase(s);
}

void	Inventory::reset() {
  this->food = 0;
  this->linemate = 0;
  this->deraumere = 0;
  this->sibur = 0;
  this->mendiane = 0;
  this->phiras = 0;
  this->thystame = 0;
  this->player = 0;
}

void	Inventory::fillInventory(std::vector<std::string> & tab) {
  void	(Inventory::*fn_ptr[7])(unsigned int);
  std::vector<std::string> ref;
  fn_ptr[0] = &Inventory::fillFood;
  fn_ptr[1] = &Inventory::fillLinemate;
  fn_ptr[2] = &Inventory::fillDeraumere;
  fn_ptr[3] = &Inventory::fillSibur;
  fn_ptr[4] = &Inventory::fillMendiane;
  fn_ptr[5] = &Inventory::fillPhiras;
  fn_ptr[6] = &Inventory::fillThystame;
  ref.push_back("nourriture");
  ref.push_back("linemate");
  ref.push_back("deraumere");
  ref.push_back("sibur");
  ref.push_back("mendiane");
  ref.push_back("phiras");
  ref.push_back("thystame");

  unsigned int	i;
  std::string	value;
  unsigned int	nb;
  for (std::vector<std::string>::iterator it = tab.begin() ; it != tab.end() ; ) {
    i = 0;
    if ((*it)[(*it).length() - 1] == '}')
      (*it)[(*it).length() - 1] = 0;
    while (i < 7 && (*it).compare(0, ref[i].length(), ref[i]) != 0)
      i += 1;
    if (i < 7) {
      value = (*it).substr(ref[i].length());
      std::istringstream buffer(value);
      buffer >> nb;
      (this->*fn_ptr[i])(nb);
    }
    ++it;
  }
}

void  Inventory::addInv(std::string & s) {
  std::vector<std::string>	tab;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(",")) != std::string::npos) {
    token = s.substr(0, pos);
    if (token.length() > 2) {
      if (token[0] == '{' || token[0] == ' ')
	tab.push_back(token.substr(1, token.length() - 1));
      else
	tab.push_back(token);
    }
    s.erase(0, pos + 1);
  }
  if (s.length() > 2) {
    if (s[0] == '{' || s[0] == ' ')
      tab.push_back(s.substr(1, s.length() - 1));
    else
      tab.push_back(s);
  }
  this->fillInventory(tab);
}

void	Inventory::fillCase(std::vector<std::string> & tab) {
  void	(Inventory::*fn_ptr[8])(unsigned int);
  std::vector<std::string> ref;
  fn_ptr[0] = &Inventory::fillFood;
  fn_ptr[1] = &Inventory::fillLinemate;
  fn_ptr[2] = &Inventory::fillDeraumere;
  fn_ptr[3] = &Inventory::fillSibur;
  fn_ptr[4] = &Inventory::fillMendiane;
  fn_ptr[5] = &Inventory::fillPhiras;
  fn_ptr[6] = &Inventory::fillThystame;
  fn_ptr[7] = &Inventory::fillPlayer;
  ref.push_back("nourriture");
  ref.push_back("linemate");
  ref.push_back("deraumere");
  ref.push_back("sibur");
  ref.push_back("mendiane");
  ref.push_back("phiras");
  ref.push_back("thystame");
  ref.push_back("joueur");

  unsigned int	i;
  for (std::vector<std::string>::iterator it = tab.begin() ; it != tab.end() ; ) {
    i = 0;
    if ((*it)[(*it).length() - 1] == '}')
      (*it)[(*it).length() - 1] = 0;
    while (i < 8 && (*it).compare(0, ref[i].length(), ref[i]) != 0)
      i += 1;
    if (i < 8) {
      (this->*fn_ptr[i])(1);
    }
    ++it;
  }
}

void	Inventory::addSawCase(std::string & s) {
  std::vector<std::string>	tab;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(" ")) != std::string::npos) {
    token = s.substr(0, pos);
    if (token.length() > 2) {
      if (token[0] == '{' || token[0] == ' ')
	tab.push_back(token.substr(1, token.length() - 1));
      else
	tab.push_back(token);
    }
    s.erase(0, pos + 1);
  }
  if (s.length() > 2) {
    if (s[0] == '{' || s[0] == ' ')
      tab.push_back(s.substr(1, s.length() - 1));
    else
      tab.push_back(s);
  }
  this->fillCase(tab);
}

void	Inventory::fillFood(unsigned int nb) {
  this->food += nb;
}

void	Inventory::fillLinemate(unsigned int nb) {
  this->linemate += nb;
}

void	Inventory::fillDeraumere(unsigned int nb) {
  this->deraumere += nb;
}

void	Inventory::fillSibur(unsigned int nb) {
  this->sibur += nb;
}

void	Inventory::fillMendiane(unsigned int nb) {
  this->mendiane += nb;
}

void	Inventory::fillPhiras(unsigned int nb) {
  this->phiras += nb;
}

void	Inventory::fillThystame(unsigned int nb) {
  this->thystame += nb;
}

void	Inventory::fillPlayer(unsigned int nb) {
  this->player += nb;
}

std::ostream    &operator<<(std::ostream & os, const Inventory & elem) {
  os << "\nnourriture : " << elem.food
     << "\nlinemate   : " << elem.linemate
     << "\nderaumere  : " << elem.deraumere
     << "\nsibur      : " << elem.sibur
     << "\nmendiane   : " << elem.mendiane
     << "\nphiras     : " << elem.phiras
     << "\nthystame   : " << elem.thystame
     << "\njoueur     : " << elem.player
     << std::endl;
  return os;
}
