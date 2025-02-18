#include "socket/poller.h"

using namespace melon::socket;

Poller::Poller()
  : m_max_conn(0)
  , m_max_fd(0)
{
}
     
Poller::~Poller()
{
  if (m_fds != nullptr)
  {
    delete[] m_fds;
    m_fds = nullptr;
  }
}
      
void Poller::create(int max_conn)
{
  m_fds = new pollfd[max_conn];
  for (int i = 0; i < max_conn; ++ i)
    m_fds[i].fd = -1;
  m_max_conn = max_conn;
}

void Poller::addFd(int fd)
{
  for (int i = 0; i < m_max_conn; ++ i)
    if (m_fds[i].fd == -1)
    {
      m_fds[i].fd = fd;
      m_fds[i].events = POLLIN | POLLHUP | POLLERR;
      m_fds_map[fd] = i;

      if (m_max_fd < i)
        m_max_fd = i;

      return;
    }
}

void Poller::delFd(int fd)
{
  auto it = m_fds_map.find(fd);
  if (it == m_fds_map.end())
    return;
  m_fds[it->second].fd = -1;
}

int Poller::poll(int timeout)
{
  return ::poll(m_fds, m_max_fd + 1, timeout);
}

bool Poller::isSet(int index, short events)
{
  return m_fds[index].revents & events;
}
    
int Poller::maxFd()
{
  return m_max_fd;
}

int Poller::getFd(int index)
{
  return m_fds[index].fd;
}
