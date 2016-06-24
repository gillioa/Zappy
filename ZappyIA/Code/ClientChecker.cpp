
#include "Client.hpp"

bool	Client::inventaireChecker() const {
  bool	(Client::*fn_ptr[7])() const;
  fn_ptr[0] = &Client::inventaireCheckerLvl1;
  fn_ptr[1] = &Client::inventaireCheckerLvl2;
  fn_ptr[2] = &Client::inventaireCheckerLvl3;
  fn_ptr[3] = &Client::inventaireCheckerLvl4;
  fn_ptr[4] = &Client::inventaireCheckerLvl5;
  fn_ptr[5] = &Client::inventaireCheckerLvl6;
  fn_ptr[6] = &Client::inventaireCheckerLvl7;
  if (this->lvl > 0 && this->lvl < 8)
    return (this->*fn_ptr[this->lvl - 1])();
  return false;
}

bool	Client::inventaireCheckerLvl1() const {
  const Inventory	inv = this->getInventory();
  if (inv.linemate >= 1)
    return true;
  return false;
}

bool	Client::inventaireCheckerLvl2() const {
  const Inventory	inv = this->getInventory();
  if (inv.linemate >= 1 && inv.deraumere >= 1 && inv.sibur >= 1)
    return true;
  return false;
}

bool	Client::inventaireCheckerLvl3() const {
  const Inventory	inv = this->getInventory();
  if (inv.linemate >= 2 && inv.phiras >= 2 && inv.sibur >= 1)
    return true;
  return false;
}

bool	Client::inventaireCheckerLvl4() const {
  const Inventory	inv = this->getInventory();
  if (inv.linemate >= 1 && inv.deraumere >= 1 && inv.sibur >= 2 && inv.phiras >= 1)
    return true;
  return false;
}

bool	Client::inventaireCheckerLvl5() const {
  const Inventory	inv = this->getInventory();
  if (inv.linemate >= 1 && inv.deraumere >= 2 && inv.sibur >= 1 && inv.mendiane >= 3)
    return true;
  return false;
}

bool	Client::inventaireCheckerLvl6() const {
  const Inventory	inv = this->getInventory();
  if (inv.linemate >= 1 && inv.deraumere >= 2 && inv.sibur >= 3 && inv.phiras >= 1)
    return true;
  return false;
}

bool	Client::inventaireCheckerLvl7() const {
  const Inventory	inv = this->getInventory();
  if (inv.linemate >= 2 && inv.deraumere >= 2 && inv.sibur >= 2 &&
      inv.mendiane >= 2 && inv.phiras >= 2 && inv.thystame >= 1)
    return true;
  return false;
}

void	Client::rdxForIncantation() {
  void	(Client::*fn_ptr[7])();
  fn_ptr[0] = &Client::rdxForIncantationLvl1;
  fn_ptr[1] = &Client::rdxForIncantationLvl2;
  fn_ptr[2] = &Client::rdxForIncantationLvl3;
  fn_ptr[3] = &Client::rdxForIncantationLvl4;
  fn_ptr[4] = &Client::rdxForIncantationLvl5;
  fn_ptr[5] = &Client::rdxForIncantationLvl6;
  fn_ptr[6] = &Client::rdxForIncantationLvl7;
  if (this->lvl > 0 && this->lvl < 8)
    (this->*fn_ptr[this->lvl - 1])();
}

void	Client::rdxForIncantationLvl1() {
  this->nextCmd = Voir;
  this->onFarm = false;
}

void	Client::rdxForIncantationLvl2() {
  this->onFarm = false;
  if (this->lastSaw.size() > 0 && this->lastSaw[0] && this->lastSaw[0]->player >= 2) {
    this->waitingMore = false;
    this->nextCmd = Voir;
  }
  else {
    this->waitingMore = true; 
    if (this->enoughFollowers() == false)
      this->nextCmd = RFI;
    else
      this->nextCmd = Voir;
 }
}

void	Client::rdxForIncantationLvl3() {
  this->onFarm = false;
  if (this->lastSaw.size() > 0 && this->lastSaw[0] && this->lastSaw[0]->player >= 2) {
    this->waitingMore = false;
    this->nextCmd = Voir;
  }
  else {
    this->waitingMore = true;
    if (this->enoughFollowers() == false)
      this->nextCmd = RFI;
    else
      this->nextCmd = Voir;
  }
}

void	Client::rdxForIncantationLvl4() {
  this->onFarm = false;
  if (this->lastSaw.size() > 0 && this->lastSaw[0] && this->lastSaw[0]->player >= 4) {
    this->waitingMore = false;
    this->nextCmd = Voir;
  }
  else {
    this->waitingMore = true;
    if (this->enoughFollowers() == false)
      this->nextCmd = RFI;
    else
      this->nextCmd = Voir;
  }
}

void	Client::rdxForIncantationLvl5() {
  this->onFarm = false;
  if (this->lastSaw.size() > 0 && this->lastSaw[0] && this->lastSaw[0]->player >= 4) {
    this->waitingMore = false;
    this->nextCmd = Voir;
  }
  else {
    this->waitingMore = true;
    if (this->enoughFollowers() == false)
      this->nextCmd = RFI;
    else
      this->nextCmd = Voir;
  }
}

void	Client::rdxForIncantationLvl6() {
  this->onFarm = false;
  if (this->lastSaw.size() > 0 && this->lastSaw[0] && this->lastSaw[0]->player >= 6) {
    this->waitingMore = false;
    this->nextCmd = Voir;
  }
  else {
    this->waitingMore = true;
    if (this->enoughFollowers() == false)
      this->nextCmd = RFI;
    else
      this->nextCmd = Voir;
  }
}

void	Client::rdxForIncantationLvl7() {
  this->onFarm = false;
  if (this->lastSaw.size() > 0 && this->lastSaw[0] && this->lastSaw[0]->player >= 6) {
    this->waitingMore = false;
    this->nextCmd = Voir;
  }
  else {
    this->waitingMore = true;
    if (this->enoughFollowers() == false)
      this->nextCmd = RFI;
    else
      this->nextCmd = Voir;
  }
}

void	Client::getMyNum(std::string & str) {
  unsigned int	i = 0;
  while (str[i] >= '0' && str[i] <= '9')
    i += 1;
  str[i] = 0;
}

bool	Client::enoughFollowers() const {
  bool	(Client::*fn_ptr[7])() const;
  fn_ptr[0] = &Client::enFolloLvl1;
  fn_ptr[1] = &Client::enFolloLvl2;
  fn_ptr[2] = &Client::enFolloLvl3;
  fn_ptr[3] = &Client::enFolloLvl4;
  fn_ptr[4] = &Client::enFolloLvl5;
  fn_ptr[5] = &Client::enFolloLvl6;
  fn_ptr[6] = &Client::enFolloLvl7;
  if (this->lvl > 0 && this->lvl < 8)
    return (this->*fn_ptr[this->lvl - 1])();  
  return false;
}

bool	Client::enFolloLvl1() const {
  return true;
}

bool	Client::enFolloLvl2() const {
  if (this->followers.size() >= 1)
    return true;
  return false;
}

bool	Client::enFolloLvl3() const {
  if (this->followers.size() >= 1)
    return true;
  return false;
}

bool	Client::enFolloLvl4() const {
  if (this->followers.size() >= 3)
    return true;
  return false;
}

bool	Client::enFolloLvl5() const {
  if (this->followers.size() >= 3)
    return true;
  return false;
}

bool	Client::enFolloLvl6() const {
  if (this->followers.size() >= 5)
    return true;
  return false;
}

bool	Client::enFolloLvl7() const {
  if (this->followers.size() >= 5)
    return true;
  return false;
}
