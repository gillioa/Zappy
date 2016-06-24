
#ifndef CLIENT_HPP_
# define CLIENT_HPP_

#include <queue>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include "EnumCmd.hpp"
#include "Inventory.hpp"

using boost::asio::ip::tcp;

class Client
{
public:
  enum { max_read_length = 4096 };
  Client(boost::asio::io_service &, tcp::resolver::iterator, char *);
  ~Client();
  int				doSomeClean();
  char				getLastDirBroad() const;
  bool				canWrite() const;
  bool				getRun() const;
  bool				getLead() const;
  void				waitingIncantationFunction(CmdType &);
  void				actingFarmingRoutine();
  void				routineFunction(int &);
  void				write_string(const std::string &);
  void				write_char(const char msg);
  void				close();
  void				setCanWrite(bool);
  void				setNextCmd(CmdType);
  void				setKey(const std::string &);
  void				setSaw(std::string &);
  void				setLead(bool);
  void				setLastDirBroad(char);
  void				setLvl(unsigned int);
  void				setInventory(std::string &);
  void				waitingForMoreClient();
  void				treatBroadcastRcv();
  void				chooseDirectionToJoin();
  void				setID();
  void				getMyNum(std::string &);
  void				resetStat();
  void				initNextCmd();
  void				getRetQueue(CmdType &);
  void				interChange();
  void				setToFollow(const std::string &);
  void				clearFollowers();
  bool				idIsInVector(std::vector<std::string>) const;
  bool				idIsNotPresent(std::string &) const;
  CmdType			getNextCmd() const;
  unsigned int			getKey() const;
  unsigned int			getLvl() const;
  Inventory			getInventory() const;
  Inventory			lastInventory;
  const std::string &		getID() const;
  std::queue<CmdType>		toRcv;
  std::vector<Inventory *>	lastSaw;
  std::vector<Inventory *> &	getLastSaw();
  std::vector<std::string> 	getFollowers() const;
  std::vector<std::string>	getIDVector(std::string &);
  const std::string &		getTeamName() const;
  const std::string &		getToFollow() const;

public:
  bool				inventaireChecker() const;
  bool				enoughFollowers() const;
  void				rdxForIncantation();
private:
  bool				inventaireCheckerLvl1() const;
  bool				inventaireCheckerLvl2() const;
  bool				inventaireCheckerLvl3() const;
  bool				inventaireCheckerLvl4() const;
  bool				inventaireCheckerLvl5() const;
  bool				inventaireCheckerLvl6() const;
  bool				inventaireCheckerLvl7() const;
  bool				enFolloLvl1() const;
  bool				enFolloLvl2() const;
  bool				enFolloLvl3() const;
  bool				enFolloLvl4() const;
  bool				enFolloLvl5() const;
  bool				enFolloLvl6() const;
  bool				enFolloLvl7() const;
  void				rdxForIncantationLvl1();
  void				rdxForIncantationLvl2();
  void				rdxForIncantationLvl3();
  void				rdxForIncantationLvl4();
  void				rdxForIncantationLvl5();
  void				rdxForIncantationLvl6();
  void				rdxForIncantationLvl7();
private:
  void				chooseNextCmd();
  void				connect_start(tcp::resolver::iterator);
  void				connect_complete(const boost::system::error_code &, tcp::resolver::iterator);
  void				read_start();
  void				read_complete(const boost::system::error_code &, size_t);
  void				do_write(const char msg);
  void				write_start();
  void				write_complete(const boost::system::error_code &);
  void				do_close();

private:
  boost::asio::io_service&	io_service;
  tcp::socket			socket;
  char				read_msg[max_read_length];
  std::deque<char>		write_msgs;
  bool				can_write;
  CmdType			nextCmd;
  std::string			final_msg;
  std::string			save_final_msg;
  std::string			teamName;
  std::string			toFollow;
  size_t			msg_len;
  bool				run;
  unsigned int			key;
  bool				lead;
  bool				onFarm;
  char				lastDirBroad;
  int				lvl;
  bool				waitingMore;
  bool				paras;
  bool				toJoin;
  bool				rcvBro;
  std::vector<std::string>	followers;
  std::string			id;
  unsigned int			resCounter;
};

#endif
