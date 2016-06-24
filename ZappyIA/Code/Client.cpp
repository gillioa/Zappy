
#include <unistd.h>
#include "Client.hpp"

Client::Client(boost::asio::io_service& io_s, tcp::resolver::iterator endpoint_iterator, char *tn)
  : io_service(io_s), socket(io_s) {
  std::string str(tn);
  this->nextCmd = None;
  this->can_write = false;
  this->final_msg = "";
  this->msg_len = 0;
  this->run = true;
  this->key = 0;
  this->onFarm = true;
  this->lastDirBroad = '0';
  this->lead = true;
  this->lvl = 1;
  this->waitingMore = false;
  this->paras = false;
  this->toJoin = false;
  this->teamName = str;
  this->rcvBro = true;
  this->toFollow = "";
  this->resCounter = 0;
  this->connect_start(endpoint_iterator);
}

Client::~Client() {
  this->followers.clear();
  for (std::vector<Inventory *>::iterator it = this->lastSaw.begin() ; it != this->lastSaw.end() ; ++it)
    delete (*it);
  this->lastSaw.clear();
}

void	Client::write_string(const std::string & msg) {
  for (std::string::const_iterator it = msg.begin() ; it != msg.end() ; ++it)
    this->write_char(*it);
  this->can_write = false;
}

void	Client::write_char(const char msg) {
  this->io_service.post(boost::bind(&Client::do_write, this, msg));
}

void	Client::close() {
  this->io_service.post(boost::bind(&Client::do_close, this));
}

bool	Client::canWrite() const {
  return this->can_write;
}

void	Client::setCanWrite(bool s) {
  this->can_write = s;
}

CmdType	Client::getNextCmd() const {
  return this->nextCmd;
}

bool	Client::getRun() const {
  return this->run;
}

void	Client::setNextCmd(CmdType c) {
  this->nextCmd = c;
}

void	Client::connect_start(tcp::resolver::iterator endpoint_iterator) {
  tcp::endpoint endpoint = *endpoint_iterator;
  this->socket.async_connect(endpoint,
			     boost::bind(&Client::connect_complete,
					 this,
					 boost::asio::placeholders::error,
					 ++endpoint_iterator));
}

void	Client::connect_complete(const boost::system::error_code & error, tcp::resolver::iterator endpoint_iterator) {
  if (!error) {
    this->read_start();
  }
  else if (endpoint_iterator != tcp::resolver::iterator()) {
      this->socket.close();
      this->connect_start(endpoint_iterator);
      this->run = false;
    }
  else {
    std::cout << "Stop : cannot be connected to the host server. [bad ip | bad port]" << std::endl;
    this->run = false;
  }
}

void	Client::read_start() {
  this->socket.async_read_some(boost::asio::buffer(read_msg, max_read_length),
			       boost::bind(&Client::read_complete, this, boost::asio::placeholders::error,
					   boost::asio::placeholders::bytes_transferred));
}

void	Client::waitingForMoreClient() {
  if (this->nextCmd == Voir) {
    this->rdxForIncantation();
    return ;
  }
  this->nextCmd = GoForIncante;
  this->can_write = true;
}

void	Client::chooseDirectionToJoin() {
  if (this->lastDirBroad == '3' || this->lastDirBroad == '4' || this->lastDirBroad == '5')
    this->nextCmd = Gauche;
  else if (this->lastDirBroad == '6' || this->lastDirBroad == '7')
    this->nextCmd = Droite;
  else if (this->lastDirBroad == '0') {
    this->nextCmd = None;
    this->rcvBro = false;
  }
  else
    this->nextCmd = Avance;
}

void	Client::treatBroadcastRcv() {
  std::stringstream	ss;
  this->lastDirBroad = this->final_msg[8];
  ss << this->lvl;
  std::string		toRcv = this->final_msg.substr(10);
  std::string		toCmp = ss.str();
  std::string		toCmp2 = ss.str();
  std::string		toCmp3 = ss.str();
  toCmp = "IncantationLvl" + toCmp + this->teamName + ":";
  toCmp2 = "OKLvl" + toCmp2 + this->teamName + ":" + this->id + ":";
  toCmp3 = "RFILvl" + toCmp3 + this->teamName + ":";

  this->paras = true;
  if (this->rcvBro) {
    if (toRcv.compare(0, toCmp.length(), toCmp) == 0) {
      std::string		ids = toRcv.substr(toCmp.length());
      std::vector<std::string>	t = this->getIDVector(ids);
      this->toFollow = "";
      this->resCounter = 0;
      if (this->idIsInVector(t) == true) {
	chooseDirectionToJoin();
	this->toJoin = true;
	this->onFarm = false;
	this->waitingMore = false;
	this->paras = false;
      }
      else {
	this->toJoin = false;
      }
    }
    else if (toRcv.compare(0, toCmp2.length(), toCmp2) == 0) {
      std::string		fol = toRcv.substr(toCmp2.length());
      if (this->enoughFollowers() == false && this->idIsNotPresent(fol)) {
	this->followers.push_back(fol);
	if (this->enoughFollowers() == true)
	  this->nextCmd = GoForIncante;
	else
	  this->nextCmd = RFI;
      }
    }
    else if (toRcv.compare(0, toCmp3.length(), toCmp3) == 0 && this->toJoin == false && this->followers.size() == 0) {
      this->toFollow = toRcv.substr(toCmp3.length());
      this->getMyNum(this->toFollow);
      this->nextCmd = ResRFI;
      this->resCounter = 0;
      this->toJoin = false;
      this->paras = false;
    }
  }
}

int	Client::doSomeClean() {
  std::string	s(this->final_msg.c_str());
  std::string	del = "\n";
  size_t	pos = 0;
  std::string	token;
  std::string	t;
  std::vector<std::string>	vec;

  while ((pos = s.find(del)) != std::string::npos) {
    token = s.substr(0, pos);
    vec.push_back(token);
    this->final_msg = token;
    s.erase(0, pos + del.length());
  }
  vec.push_back(s);
  if (vec.size() > 1) {
    for (std::vector<std::string>::iterator it = vec.begin() ; it != vec.end() ; ++it)
      this->final_msg = (*it);
    this->chooseNextCmd();
    return 1;
  }
  return 0;
}

void	Client::initNextCmd() {
  this->paras = false;
  if (this->toFollow != "" && this->followers.size() != 0)
    this->resetStat();
}

void	Client::getRetQueue(CmdType & next) {
  if (this->toRcv.size() > 0 && this->paras == false) {
    if (this->toRcv.size() > 1)
      this->paras = true;
    next = this->toRcv.front();
    this->toRcv.pop();
  }
}

void	Client::interChange() {
  if (this->final_msg.compare(0, 13, "niveau actuel") == 0) {
    this->resetStat();
    this->lvl += 1;
  }
  else if (this->final_msg.compare(0, 2, "ko") == 0)
    this->resetStat();
}

void	Client::waitingIncantationFunction(CmdType & next) {
  if (next == Voir && this->waitingMore == true) {
    this->setSaw(this->final_msg);
    this->nextCmd = None;
  }
}

void	Client::actingFarmingRoutine() {
  if (this->final_msg.compare(0, 2, "ok") != 0 && this->final_msg.compare(0, 2, "ko") != 0)
    this->setSaw(this->final_msg);
  if (this->onFarm)
    this->nextCmd = Prendre;
  else 
    this->nextCmd = PrendreMid;
}

void	Client::routineFunction(int & p) {
  if (p % 9 == 0 && p > 18)
    this->nextCmd = Inventaire;
  else if (p % 11 == 0)
    this->nextCmd = Droite;
  else if (p % 2 == 0)
    this->nextCmd = Voir;
  else
    this->nextCmd = Avance;
  p += 1;
}

void	Client::chooseNextCmd() {
  CmdType	next = None;
  static int p = 1;

  if (p != 1)
    if (this->doSomeClean() == 1)
      return ;
  this->initNextCmd();
  if (this->final_msg.length() > 11 && this->final_msg.compare(0, 8, "message ") == 0) {
    this->treatBroadcastRcv();
    return ;
  }
  this->getRetQueue(next);
  this->interChange();
  if (this->toJoin == true) {
    if (this->nextCmd != Avance && this->nextCmd != Droite && this->nextCmd != Gauche)
      this->nextCmd = None;
    return ;
  }
  if (this->nextCmd == Incantation)
    return ;
  if (next == Inventaire) {
    this->setInventory(this->final_msg);
    if (this->inventaireChecker() == true) {
      this->rdxForIncantation();
      return ;
    }
  }
  this->waitingIncantationFunction(next);
  if (this->waitingMore == true) {
    this->waitingForMoreClient();
    return ;
  }
  if (next == Voir)
    this->actingFarmingRoutine();
  else if (this->onFarm)
    this->routineFunction(p);
  else
    this->nextCmd = None;
}

void	Client::read_complete(const boost::system::error_code & error, size_t bytes_transferred) {
  if (!error) {
    this->read_msg[bytes_transferred] = 0;
    this->final_msg += std::string(this->read_msg);
    this->msg_len += bytes_transferred;
    if (this->read_msg[bytes_transferred - 1] == 10) {
      this->final_msg[this->msg_len - 1] = 0;
      this->chooseNextCmd();
      this->final_msg = "";
      this->msg_len = 0;
      if (this->paras == false)
	this->can_write = true;
    }
    this->read_start();
  }
  else {
    this->do_close();
    this->run = false;
  }
}

void	Client::do_write(const char msg) {
  bool write_in_progress = !(this->write_msgs.empty());
  this->write_msgs.push_back(msg);
  if (!write_in_progress)
    write_start();
}

void	Client::write_start() {
  boost::asio::async_write(this->socket,
			   boost::asio::buffer(&this->write_msgs.front(), 1),
			   boost::bind(&Client::write_complete,
				       this,
				       boost::asio::placeholders::error));
}

void	Client::write_complete(const boost::system::error_code& error) {
  if (!error) {
    this->write_msgs.pop_front();
    if (!(this->write_msgs.empty()))
      this->write_start();
  }
  else
    this->do_close();
}

void	Client::do_close() {
  this->socket.close();
}

void	Client::setKey(const std::string & stringKey) {
  for(std::string::const_iterator it = stringKey.begin() ; it != stringKey.end() ; ++it)
    this->key += *it;
}

unsigned int	Client::getKey() const {
  return this->key;
}

std::vector<Inventory *> &	Client::getLastSaw() {
  return this->lastSaw;
}

void				Client::setSaw(std::string & s) {
  std::vector<std::string>      tab;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(",")) != std::string::npos) {
    token = s.substr(0, pos);
    if (token[0] == '{' || token[0] == ' ')
      tab.push_back(token.substr(1, token.length() - 1));
    else
      tab.push_back(token);
    s.erase(0, pos + 1);
  }
  if (s[0] == '{' || s[0] == ' ')
    tab.push_back(s.substr(1, s.length() - 1));
  else
    tab.push_back(s);
  for (std::vector<Inventory *>::iterator it = this->lastSaw.begin() ; it != this->lastSaw.end() ; ++it)
    delete (*it);
  this->lastSaw.clear();
  for (std::vector<std::string>::iterator it = tab.begin() ; it != tab.end() ; ) {
    this->lastSaw.push_back(new Inventory((*it)));
    ++it;
  }
}

void				Client::setLead(bool l) {
  this->lead = l;
}

bool				Client::getLead() const {
  return this->lead;
}

char				Client::getLastDirBroad() const {
  return this->lastDirBroad;
}

void				Client::setLastDirBroad(char d) {
  this->lastDirBroad = d;
}

void				Client::setLvl(unsigned int l) {
  this->lvl = l;
}

void				Client::setInventory(std::string & s) {
  this->lastInventory.reset();
  this->lastInventory.addInv(s);
}

Inventory			Client::getInventory() const {
  return this->lastInventory;
}

unsigned int			Client::getLvl() const {
  return this->lvl;
}

const std::string &		Client::getTeamName() const {
  return this->teamName;
}

#include <stdlib.h>

void				Client::setID() {
  struct timeval time;
  gettimeofday(&time, NULL);
  srand(time.tv_usec);
  unsigned int nb = rand() % 8999 + 1000;
  std::stringstream	ss;
  ss << nb;
  this->id = ss.str();
}

const std::string &		Client::getID() const {
  return this->id;
}

const std::string &		Client::getToFollow() const {
  return this->toFollow;
}

std::vector<std::string>	Client::getFollowers() const {
  return this->followers;
}

void				Client::resetStat() {
  this->final_msg = "";
  this->onFarm = true;
  this->toJoin = false;
  this->followers.clear();
  this->toFollow = "";
  this->rcvBro = true;
  this->waitingMore = false;
  this->paras = false;
  this->resCounter = 0;
}

std::vector<std::string>		Client::getIDVector(std::string & s) {
  std::vector<std::string>	t;
  size_t			pos = 0;
  std::string			token;

  while ((pos = s.find(":")) != std::string::npos) {
    token = s.substr(0, pos);
    t.push_back(token);
    s.erase(0, pos + 1);
  }
  return t;
}

bool					Client::idIsInVector(std::vector<std::string> t) const {
  unsigned int	i = 0;

  while (i < t.size()) {
    if (t[i].substr(0, 4).compare(this->id.substr(0, 4)) == 0)
      return true;
    i += 1;
  }
  return false;
}

bool					Client::idIsNotPresent(std::string & s) const {
  unsigned int	i = 0;

  while (i < this->followers.size()) {
    if (this->followers[i].substr(0, 4).compare(s.substr(0, 4)) == 0)
      return false;
    i += 1;
  }
  return true;
}

void					Client::setToFollow(const std::string & s) {
  this->toFollow = s;
}

void					Client::clearFollowers() {
  this->followers.clear();
}
