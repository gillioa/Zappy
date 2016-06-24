#ifndef EGG_HPP_
#define EGG_HPP_

#include <mutex>

enum eEggStat {
  Eclot = 0,
  Rien,
};

class Egg
{
  unsigned int _posX;
  unsigned int _posY;
  eEggStat _stat;
  int _id;
  std::mutex m_mutex; 
public:
  Egg(int, unsigned int, unsigned int);
  ~Egg();
  eEggStat getStat() const;
  void setStat(eEggStat);
  void setX(unsigned int);
  void setY(unsigned int);
  unsigned int getX() const;
  unsigned int getY() const;
  int getId() const;
};

#endif
