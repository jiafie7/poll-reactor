#pragma once

#include "socket/server_socket.h"
#include "socket/poller.h"

#include "thread/mutex.h"
using namespace melon::thread;

namespace melon
{
  namespace socket
  {
    class SocketHandler
    {
      SINGLETON(SocketHandler);
    public:
      void listen(const std::string& ip, int port);
      void attach(int fd);
      void detach(int fd);
      void handle(int max_conn, int timeout);

    private:
      Socket* m_server = nullptr;
      Poller m_poller;
      Mutex m_mutex;
    };
  }
}
