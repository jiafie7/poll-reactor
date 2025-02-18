#pragma once

#include "socket/socket.h"
using namespace melon::socket;

#include "thread/task.h"
using namespace melon::thread;

namespace melon
{
  namespace task
  {
    class EchoTask : public Task
    {
    public:
      EchoTask() = delete;
      EchoTask(int socket_fd);
      ~EchoTask();

      void run();
      void destroy();

    private:
      int m_socket_fd = 0;
      bool m_closed = false;
    };
  }
}
