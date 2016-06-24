#ifndef TREATMENT_HPP_
#define TREATMENT_HPP_

#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "Zappy.hpp"

class Treatment
{
public:
  Treatment();
  ~Treatment();
  unsigned int StringToUInt(std::string const &);
  unsigned int generateRandomNumber(unsigned int, unsigned int) const;
  int StringToInt(std::string const &);
  bool getSubstr(std::string const &command, unsigned int i, std::string &res);
  bool doMsz(std::string const &, Zappy &);
  bool doBct(std::string const &, Zappy &);
  bool doTna(std::string const &, Zappy &);
  bool doPnw(std::string const &, Zappy &);
  bool doPpo(std::string const &, Zappy &);
  bool doPlv(std::string const &, Zappy &);
  bool doPin(std::string const &, Zappy &);
  bool doPex(std::string const &, Zappy &);
  bool doPbc(std::string const &, Zappy &);
  bool doPic(std::string const &, Zappy &);
  bool doPie(std::string const &, Zappy &);
  bool doPfk(std::string const &, Zappy &);
  bool doPdr(std::string const &, Zappy &);
  bool doPgt(std::string const &, Zappy &);
  bool doPdi(std::string const &, Zappy &);
  bool doEnw(std::string const &, Zappy &);
  bool doEht(std::string const &, Zappy &);
  bool doEbo(std::string const &, Zappy &);
  bool doEdi(std::string const &, Zappy &);
  bool doSgt(std::string const &, Zappy &);
  bool doSeg(std::string const &, Zappy &);
  bool doSmg(std::string const &, Zappy &);
  bool doSuc(std::string const &, Zappy &);
  bool doSbp(std::string const &, Zappy &);
};

#endif
