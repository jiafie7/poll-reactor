#include <iostream>

#include "frame/server.h"
using namespace melon::frame;

int main()
{  
  Singleton<Server>::getInstance()->start();
  
  return 0;
}
