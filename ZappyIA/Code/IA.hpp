
#ifndef IA_HPP_
# define IA_HPP_

#include <signal.h>
#include "Client.hpp"
#include "EnumCmd.hpp"

class IA {
private:
  Client *		c;
public:
  IA(Client *, const std::string & name);
  const std::string &	teamName;
  void			choseCmdToSend() const;
  const std::string &	getTeamName() const;
private:
  void	sendAvance(const std::string &) const;
  void	sendDroite(const std::string &) const;
  void	sendGauche(const std::string &) const;
  void	sendVoir(const std::string &) const;
  void	sendInventaire(const std::string &) const;
  void	sendPrendre(const std::string &) const;
  void	sendPose(const std::string &) const;
  void	sendExpulse(const std::string &) const;
  void	sendBroadcast(const std::string &) const;
  void	sendIncantation(const std::string &) const;
  void	sendFork(const std::string &) const;
  void	sendConnectNbr(const std::string &) const;
  void	sendNeedFood(const std::string &) const;
  void	sendGoForIncante(const std::string &) const;
  void	sendPrendreMid(const std::string &) const;
  void	sendPoseNeeded(const std::string &) const;
  void	sendMoveIt(const std::string &) const;
  void	sendRFI(const std::string &) const;
  void	sendResRFI(const std::string &) const;

private:
  const std::string	allTake() const;
  const std::string	retFood() const;
  const std::string	retLinemate() const;
  const std::string	retSibur() const;
  const std::string	retDeraumere() const;
  const std::string	retPhiras() const;
  const std::string	retThystame() const;
  const std::string	retMendiane() const;
  void			sendPoseNeededLvl1() const;
  void			sendPoseNeededLvl2() const;
  void			sendPoseNeededLvl3() const;
  void			sendPoseNeededLvl4() const;
  void			sendPoseNeededLvl5() const;
  void			sendPoseNeededLvl6() const;
  void			sendPoseNeededLvl7() const;
public:
  bool			getLead() const;
  void			setLead(bool);
  unsigned int		getLvl() const;
  void			setLvl(unsigned int);
private:
  bool			lead;
  unsigned int		lvl;
};

#endif
