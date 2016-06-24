
#include <stdio.h>
#include "IA.hpp"

bool	key_inter = true;

void	signal_callback_handler(int)
{
  key_inter = false;
  std::cout << "\rDisconnect." << std::endl;
}

void	takeArgs(std::string & av1, std::string & av2, std::string & av3, char ** argv) {
  unsigned int	i = 1;
  while (argv[i]) {
    if (std::string(argv[i]) == "-h") {
      if (argv[i + 1])
	av1 = std::string(argv[i + 1]);
    }
    else if (std::string(argv[i]) == "-p") {
      if (argv[i + 1])
	av2 = std::string(argv[i + 1]);
    }
    else if (std::string(argv[i]) == "-n") {
      if (argv[i + 1])
	av3 = std::string(argv[i + 1]);
    }
    i += 1;
  }
}

int	checkArgs(std::string & av2, std::string av3) {
  int	i = 0;
  if (av2 == "") {
    std::cout << "Error : missing option -p." << std::endl;
    i = -1;
  }
  if (av3 == "") {
    std::cout << "Error : missing option -n." << std::endl;
    i = -1;
  }
  return i;
}

void	runClient(Client & c, IA & ia) {
  unsigned int	deb = 0;
  while (c.getRun() && key_inter)
    {
      if (c.canWrite() == true) {
	deb = 0;
	ia.setLvl(c.getLvl());
	ia.choseCmdToSend();
      }
      usleep(200);
      deb += 1;
      if (deb >= 70000) {
	c.setCanWrite(true);
	c.resetStat();
	c.setNextCmd(Inventaire);
      }
    }
  c.close();
}

int     main(int argc, char ** argv)
{
  std::string	av1 = "127.0.0.1";
  std::string	av2 = "";
  std::string	av3 = "";
  takeArgs(av1, av2, av3, argv);
  if (argc <= 1 || checkArgs(av2, av3) == -1) {
    std::cerr << "Usage: " << argv[0] << " [-h <host>] -p <port> -n <team_name>\n";
    return 1;
  }
  try {
    char	*p3 = new char[av3.length() + 1];
    strcpy(p3, av3.c_str());
    signal(SIGINT, signal_callback_handler);
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(av1, av2);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    Client c(io_service, iterator, p3);
    c.setID();
    IA ia(&c, av2);
    c.write_string(av3);
    c.write_string("\n");
    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
    sleep(1);
    runClient(c, ia);
    t.detach();
    delete [] p3;
  }
  catch (boost::exception & e) {
    std::cerr << "Stop : Boost Exception." << std::endl;
    return -1;
  }
  catch (std::exception & e) {
    std::cerr << "Exception : " << e.what() << std::endl;
    return -1;
  }
  catch (...) {
    std::cerr << "Boost Exception." << std::endl;
    return -1;
  }
  return 0;
}
