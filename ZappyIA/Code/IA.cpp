
#include "IA.hpp"

IA::IA(Client * cl, const std::string & name) : teamName(name) {
  this->c = cl;
  this->lvl = 1;
}

void	IA::sendAvance(const std::string &) const {
  this->c->write_string("avance\n");
  this->c->setNextCmd(None);
  this->c->toRcv.push(Avance);
}

void	IA::sendDroite(const std::string &) const {
  this->c->write_string("droite\n");
  this->c->setNextCmd(None);
  this->c->toRcv.push(Droite);
}

void	IA::sendGauche(const std::string &) const {
  this->c->write_string("gauche\n");
  this->c->setNextCmd(None);
  this->c->toRcv.push(Gauche);
}

void	IA::sendVoir(const std::string &) const {
  this->c->write_string("voir\n");
  this->c->toRcv.push(Voir);
}

void	IA::sendInventaire(const std::string &) const {
  this->c->write_string("inventaire\n");
  this->c->toRcv.push(Inventaire);
  this->c->setNextCmd(None);
  this->c->setToFollow("");
  this->c->clearFollowers();
}

const std::string	IA::retFood() const {
  this->c->lastSaw[0]->food -= 1;
  return "nourriture";
}

const std::string	IA::retLinemate() const {
  this->c->lastSaw[0]->linemate -= 1;
  return "linemate";
}

const std::string	IA::retDeraumere() const {
  this->c->lastSaw[0]->deraumere -= 1;
  return "deraumere";
}

const std::string	IA::retSibur() const {
  this->c->lastSaw[0]->sibur -= 1;
  return "sibur";
}

const std::string	IA::retMendiane() const {
  this->c->lastSaw[0]->mendiane -= 1;
  return "mendiane";
}

const std::string	IA::retPhiras() const {
  this->c->lastSaw[0]->phiras -= 1;
  return "phiras";
}

const std::string	IA::retThystame() const {
  this->c->lastSaw[0]->thystame -= 1;
  return "thystame";
}

const std::string   	IA::allTake() const {
  const std::string	(IA::*fn_ptr[7])() const;
  std::vector<unsigned int> ref;
  unsigned int i = 0;
  ref.push_back(this->c->lastSaw[0]->food);
  ref.push_back(this->c->lastSaw[0]->linemate);
  ref.push_back(this->c->lastSaw[0]->deraumere);
  ref.push_back(this->c->lastSaw[0]->sibur);
  ref.push_back(this->c->lastSaw[0]->mendiane);
  ref.push_back(this->c->lastSaw[0]->phiras);
  ref.push_back(this->c->lastSaw[0]->thystame);
  fn_ptr[0] = &IA::retFood;
  fn_ptr[1] = &IA::retLinemate;
  fn_ptr[2] = &IA::retDeraumere;
  fn_ptr[3] = &IA::retSibur;
  fn_ptr[4] = &IA::retMendiane;
  fn_ptr[5] = &IA::retPhiras;
  fn_ptr[6] = &IA::retThystame;
  while (i < 7 && ref[i] == 0)
    i += 1;
  if (i < 7)
    return (this->*fn_ptr[i])();
  return ("None");
}

void	IA::sendPrendre(const std::string &) const {
  std::string	s;
  if (this->c->lastSaw.size() > 0 && this->c->lastSaw[0] && (s = this->allTake()) != "None") {
    this->c->write_string("prend " + s + "\n");
    this->c->toRcv.push(Voir);
  }
  else {
    this->c->setCanWrite(true);
    this->c->setNextCmd(Avance);
  }
}

void	IA::sendPrendreMid(const std::string &) const {
  std::string	s;
  if (this->c->lastSaw.size() > 0 && this->c->lastSaw[0] && (s = this->allTake()) != "None") {
    this->c->write_string("prend " + s + "\n");
    this->c->toRcv.push(Voir);
  }
  else {
    this->c->setCanWrite(true);
    this->c->setNextCmd(PoseNeeded);
  }
}

void	IA::sendPose(const std::string & obj) const {
  this->c->write_string("pose " + obj + "\n");
}

void	IA::sendExpulse(const std::string &) const {
  this->c->write_string("expulse\n");
  this->c->toRcv.push(None);
}

void	IA::sendBroadcast(const std::string & msg) const {
  std::string toSend(msg.c_str());
  this->c->write_string("broadcast " + toSend + "\n");
  this->c->toRcv.push(None);
}

void	IA::sendIncantation(const std::string &) const {
  this->c->write_string("incantation\n");
  this->c->toRcv.push(Incantation);
  this->c->setNextCmd(None);
}

void	IA::sendFork(const std::string &) const {
  this->c->write_string("fork\n");
}

void	IA::sendConnectNbr(const std::string &) const {
  this->c->write_string("connect_nbr\n");
  this->c->toRcv.push(ConnectNbr);
}

void	IA::sendNeedFood(const std::string &) const {
  this->sendBroadcast("Food!");
}

void	IA::sendGoForIncante(const std::string &) const {
  std::vector<std::string> fs = this->c->getFollowers();
  if (fs.size() > 0) {
    std::stringstream	ss;
    ss << this->lvl;
    std::string	s = ss.str();
    std::string	toSend = "IncantationLvl" + s + this->c->getTeamName() + ":";
    for (std::vector<std::string>::iterator it = fs.begin() ;
	 it != fs.end() ; ++it)
      toSend += ((*it).substr(0, 4) + ":");
    this->sendBroadcast(toSend);
    this->c->setNextCmd(Voir);
  }
  else
    this->sendRFI("");
}

void	IA::sendPoseNeeded(const std::string &) const {
  void	(IA::*fn_ptr[7])() const;
  fn_ptr[0] = &IA::sendPoseNeededLvl1;
  fn_ptr[1] = &IA::sendPoseNeededLvl2;
  fn_ptr[2] = &IA::sendPoseNeededLvl3;
  fn_ptr[3] = &IA::sendPoseNeededLvl4;
  fn_ptr[4] = &IA::sendPoseNeededLvl5;
  fn_ptr[5] = &IA::sendPoseNeededLvl6;
  fn_ptr[6] = &IA::sendPoseNeededLvl7;
  if (this->lvl > 0 && this->lvl < 8)
    (this->*fn_ptr[this->lvl - 1])();
}

void	IA::sendPoseNeededLvl1() const {
  this->sendPose("linemate");
  this->c->lastInventory.linemate -= 1;
  this->c->setNextCmd(Incantation);
}

void	IA::sendPoseNeededLvl2() const {
  this->sendPose("linemate");
  this->c->lastInventory.linemate -= 1;
  this->sendPose("deraumere");
  this->c->lastInventory.deraumere -= 1;
  this->sendPose("sibur");
  this->c->lastInventory.sibur -= 1;
  this->c->setNextCmd(Incantation);
}

void	IA::sendPoseNeededLvl3() const {
  this->sendPose("linemate");
  this->sendPose("linemate");
  this->c->lastInventory.linemate -= 2;
  this->sendPose("sibur");
  this->c->lastInventory.sibur -= 1;
  this->sendPose("phiras");
  this->sendPose("phiras");
  this->c->lastInventory.phiras -= 2;
  this->c->setNextCmd(Incantation);
}

void	IA::sendPoseNeededLvl4() const {
  this->sendPose("linemate");
  this->c->lastInventory.linemate -= 1;
  this->sendPose("deraumere");
  this->c->lastInventory.deraumere -= 1;
  this->sendPose("sibur");
  this->sendPose("sibur");
  this->c->lastInventory.sibur -= 2;
  this->sendPose("phiras");
  this->c->lastInventory.phiras -= 1;
  this->c->setNextCmd(Incantation);
}

void	IA::sendPoseNeededLvl5() const {
  this->sendPose("linemate");
  this->c->lastInventory.linemate -= 1;
  this->sendPose("deraumere");
  this->sendPose("deraumere");
  this->c->lastInventory.deraumere -= 2;
  this->sendPose("sibur");
  this->c->lastInventory.sibur -= 1;
  this->sendPose("mendiane");
  this->sendPose("mendiane");
  this->sendPose("mendiane");
  this->c->lastInventory.mendiane -= 3;
  this->c->setNextCmd(Incantation);
}

void	IA::sendPoseNeededLvl6() const {
  this->sendPose("linemate");
  this->c->lastInventory.linemate -= 1;
  this->sendPose("deraumere");
  this->sendPose("deraumere");
  this->c->lastInventory.deraumere -= 2;
  this->sendPose("sibur");
  this->sendPose("sibur");
  this->sendPose("sibur");
  this->c->lastInventory.sibur -= 3;
  this->sendPose("phiras");
  this->c->lastInventory.phiras -= 1;
  this->c->setNextCmd(Incantation);
}

void	IA::sendPoseNeededLvl7() const {
  this->sendPose("linemate");
  this->sendPose("linemate");
  this->c->lastInventory.linemate -= 2;
  this->sendPose("deraumere");
  this->sendPose("deraumere");
  this->c->lastInventory.deraumere -= 2;
  this->sendPose("sibur");
  this->sendPose("sibur");
  this->c->lastInventory.sibur -= 2;
  this->sendPose("mendiane");
  this->sendPose("mendiane");
  this->c->lastInventory.mendiane -= 2;
  this->sendPose("phiras");
  this->sendPose("phiras");
  this->c->lastInventory.phiras -= 2;
}

void	IA::sendRFI(const std::string &) const {
  std::string	toSend = "RFILvl";
  std::stringstream	ss;
  ss << this->lvl;
  toSend += ss.str();
  toSend += this->c->getTeamName();
  toSend += ":" + this->c->getID();
  this->sendBroadcast(toSend);
  this->c->toRcv.pop();
  this->c->setNextCmd(Voir);
}

void	IA::sendResRFI(const std::string &) const {
  std::stringstream	ss;
  ss << this->lvl;
  std::string	toSend = "OKLvl" + ss.str() + this->c->getTeamName() +  ":" + this->c->getToFollow().substr(0, 4) + ":" + this->c->getID();
  this->sendBroadcast(toSend);
}

void	IA::choseCmdToSend() const {
  CmdType	cmd = this->c->getNextCmd();
  const std::string msg = "";

  void	(IA::*fn_ptr[None])(const std::string &) const;
  fn_ptr[0] = &IA::sendAvance;
  fn_ptr[1] = &IA::sendDroite;
  fn_ptr[2] = &IA::sendGauche;
  fn_ptr[3] = &IA::sendVoir;
  fn_ptr[4] = &IA::sendInventaire;
  fn_ptr[5] = &IA::sendPrendre;
  fn_ptr[6] = &IA::sendPose;
  fn_ptr[7] = &IA::sendExpulse;
  fn_ptr[8] = &IA::sendBroadcast;
  fn_ptr[9] = &IA::sendIncantation;
  fn_ptr[10] = &IA::sendFork;
  fn_ptr[11] = &IA::sendConnectNbr;
  fn_ptr[12] = &IA::sendNeedFood;
  fn_ptr[13] = &IA::sendGoForIncante;
  fn_ptr[14] = &IA::sendPrendreMid;
  fn_ptr[15] = &IA::sendPoseNeeded;
  fn_ptr[16] = &IA::sendRFI;
  fn_ptr[17] = &IA::sendResRFI;
  if (cmd < None && cmd >= Avance) {
    (this->*fn_ptr[cmd])(msg);
  }
}

const std::string & IA::getTeamName() const {
  return (this->teamName);
}

bool	IA::getLead() const {
  return this->lead;
}

void	IA::setLead(bool l) {
  this->lead = l;
}

unsigned int	IA::getLvl() const {
  return this->lvl;
}

void	IA::setLvl(unsigned int l) {
  this->lvl = l;
}
