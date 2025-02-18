#pragma once

#include <map>
#include <poll.h>

namespace melon
{
  namespace socket
  {
    class Poller
    {
    public:
      Poller();
      ~Poller();

      void create(int max_conn);
      void addFd(int fd);
      void delFd(int fd);
      int poll(int timeout);
      bool isSet(int index, short events);

      int maxFd();
      int getFd(int index);

    private:
      struct pollfd* m_fds;
      int m_max_conn;
      int m_max_fd;
      std::map<int, int> m_fds_map;
    };
  }
}
