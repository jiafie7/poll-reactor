#include "socket/socket_handler.h"
using namespace melon::socket;

#include "task/task_factory.h"
using namespace melon::task;

#include "thread/auto_lock.h"
#include "thread/task_dispatcher.h"
using namespace melon::thread;

void SocketHandler::listen(const std::string& ip, int port)
{
  m_server = new ServerSocket(ip, port);
}
    
void SocketHandler::attach(int fd)
{
  AutoLock lock(&m_mutex);
  m_poller.addFd(fd); 
}

void SocketHandler::detach(int fd)
{
  AutoLock lock(&m_mutex);
  m_poller.delFd(fd);
}

void SocketHandler::handle(int max_conn, int timeout)
{
  m_poller.create(max_conn);

  attach(m_server->fd());

  while (true)
  {
    int ret = m_poller.poll(timeout);
    if (ret < 0)
    {
      log_error("socket poll error: errno = %d, errmsg = %s.", errno, strerror(errno));
      break;
    }
    else if (ret == 0)
    {
      log_debug("socket poll timeout.");
      continue;
    }
    log_debug("socket poll ok: ret = %d.", ret);

    for (int i = 0; i < m_poller.maxFd() + 1; ++ i)
    {
      if (!(m_poller.isSet(i, POLLIN | POLLHUP | POLLERR)))
        continue;
      
      if (ret -- == 0)
        break;
      
      if (i == 0)
      {
        int conn_fd = m_server->accept();
        if (conn_fd < 0)
        {
          log_error("server accept error: errno = %d, errmsg = %s.", errno, strerror(errno));
          continue;
        }
        Socket socket(conn_fd);
        socket.setNonBlocking();
        attach(conn_fd);
      }
      else
      {
        int conn_fd = m_poller.getFd(i);

        if (m_poller.isSet(i, POLLHUP))
        {
          log_error("socket hang up by peer: conn = %d.", conn_fd);
          detach(conn_fd);
          ::close(conn_fd);
        }
        else if (m_poller.isSet(i, POLLERR))
        {
          log_error("socket error: conn = %d.", conn_fd);
          detach(conn_fd);
          ::close(conn_fd);
        }
        else if (m_poller.isSet(i, POLLIN))
        {
          detach(conn_fd);

          auto task = TaskFactory::create(conn_fd);
          Singleton<TaskDispatcher>::getInstance()->push(task);
        }
      }
    }
  }
}

