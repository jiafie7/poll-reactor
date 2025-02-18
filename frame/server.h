#pragma once

#include "utility/singleton.h"
#include "utility/ini_parser.h"
#include "utility/system.h"
using namespace melon::utility;

namespace melon
{
  namespace frame
  {
    class Server
    {
      SINGLETON(Server);

    public:
      void start();
    
    private:
      std::string m_ip;
      int m_port = 0;
      int m_threads = 0;
      int m_max_conns = 0;
      int m_wait_time = 0;
      int m_log_level = 0;
    };
  }
}
