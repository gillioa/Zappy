
#ifndef INVENTORY_HPP_
# define INVENTORY_HPP_

#include <sstream>
#include <iostream>
#include <string>
#include <vector>

class Inventory {
public:
  Inventory();
  Inventory(std::string &);
  void	addInv(std::string &);
  void	addSawCase(std::string &);
  void	reset();
public:
  unsigned int	food;
  unsigned int	linemate;
  unsigned int	deraumere;
  unsigned int	sibur;
  unsigned int	mendiane;
  unsigned int	phiras;
  unsigned int	thystame;
  unsigned int	player;
private:
  void	fillInventory(std::vector<std::string> &);
  void	fillCase(std::vector<std::string> &);
  void	fillFood(unsigned int);
  void	fillLinemate(unsigned int);
  void	fillDeraumere(unsigned int);
  void	fillSibur(unsigned int);
  void	fillMendiane(unsigned int);
  void	fillPhiras(unsigned int);
  void	fillThystame(unsigned int);
  void	fillPlayer(unsigned int);
};

std::ostream    &operator<<(std::ostream &, const Inventory &);

#endif
