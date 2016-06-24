#include "App.hpp"

int main(int argc, char const *argv[])
{
  (void)argc;
  (void)argv;

  try {  
  App app;
  
  app.initialize();
  app.run();
  }
  catch (const std::exception &e) {
    std::cerr << e.what();
    return (-1);
  }
  return 0;
}
