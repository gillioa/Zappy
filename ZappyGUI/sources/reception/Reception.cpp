#include "Reception.hpp"
#include <iostream>
#include <unistd.h>

Reception::Reception(Socket &com, Zappy &data) :
_comm(com),
_buf(2048),
_data(data)
{
}

Reception::~Reception() {
}

void Reception::threadLaunch(Reception *recep)
{
  recep->launch();
}

void Reception::setFuncPointer()
{
  _tabCommand[0] = &Treatment::doMsz;
  _tabCommand[1] = &Treatment::doBct;
  _tabCommand[2] = &Treatment::doTna;
  _tabCommand[3] = &Treatment::doPnw;
  _tabCommand[4] = &Treatment::doPpo;
  _tabCommand[5] = &Treatment::doPlv;
  _tabCommand[6] = &Treatment::doPin;
  _tabCommand[7] = &Treatment::doPex;
  _tabCommand[8] = &Treatment::doPbc;
  _tabCommand[9] = &Treatment::doPic;
  _tabCommand[10] = &Treatment::doPie;
  _tabCommand[11] = &Treatment::doPfk;
  _tabCommand[12] = &Treatment::doPdr;
  _tabCommand[13] = &Treatment::doPgt;
  _tabCommand[14] = &Treatment::doPdi;
  _tabCommand[15] = &Treatment::doEnw;
  _tabCommand[16] = &Treatment::doEht;
  _tabCommand[17] = &Treatment::doEbo;
  _tabCommand[18] = &Treatment::doEdi;
  _tabCommand[19] = &Treatment::doSgt;
  _tabCommand[20] = &Treatment::doSeg;
  _tabCommand[21] = &Treatment::doSmg;
  _tabCommand[22] = &Treatment::doSuc;
  _tabCommand[23] = &Treatment::doSbp;
}

void Reception::setCmdList()
{
  _commandList.push_back("msz");
  _commandList.push_back("bct");
  _commandList.push_back("tna");
  _commandList.push_back("pnw");
  _commandList.push_back("ppo");
  _commandList.push_back("plv");
  _commandList.push_back("pin");
  _commandList.push_back("pex");
  _commandList.push_back("pbc");
  _commandList.push_back("pic");
  _commandList.push_back("pie");
  _commandList.push_back("pfk");
  _commandList.push_back("pdr");
  _commandList.push_back("pgt");
  _commandList.push_back("pdi");
  _commandList.push_back("enw");
  _commandList.push_back("eht");
  _commandList.push_back("ebo");
  _commandList.push_back("edi");
  _commandList.push_back("sgt");
  _commandList.push_back("seg");
  _commandList.push_back("smg");
  _commandList.push_back("suc");
  _commandList.push_back("sbp");
}

bool Reception::verifyData(std::string const &command)
{
  unsigned int i = 0;

  while (i < _commandList.size())
    {
      if (command.substr(0, 3) == _commandList[i]) {
	if ((_treat.*_tabCommand[i])(command, _data) == false) {
	  std::cerr << _commandList[i] << " : Invalid parameter in the command receive from server" << std::endl;
	  return (false);
	}
	else
	  return (true);
      }
      i++;
    }
  std::cerr << "Unknown command receive from server" << std::endl;
  return (false);
}

void Reception::launch()
{
  std::string str;
  std::string ret;

  setFuncPointer();
  setCmdList();
  while (42)
  {
    if (_buf.sizeEmpty() > 100)
    {
      str = _comm.readOnSocket(100);
      _buf.pushString(str);
    }
    if (!_buf.isEmpty())
    {
      if (_buf.getFirstString(ret) == true)
      {
	if (ret.compare("BIENVENUE") == 0)
	  _comm.writeOnSocket("GRAPHIC\n");
	else
	  verifyData(ret);
      }
    }
    usleep(10);
  }
}
