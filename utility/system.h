#pragma once

#include <cstring>
#include <dirent.h> // opendir
#include <string>
#include <sys/resource.h>
#include <sys/stat.h> // mkdir
#include <unistd.h>

#include "utility/singleton.h"
using namespace melon::utility;

namespace melon
{
  namespace utility
  {
    class System
    {
      SINGLETON(System);
    public:
      void init();
      std::string getRootPath();

    private:
      void coreDump();

    private:
      std::string m_root_path;
    };
  }
}
