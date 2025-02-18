#include "frame/server.h"
using namespace melon::frame;

#include <thread/task_dispatcher.h>
using namespace melon::thread;

#include <socket/socket_handler.h>
using namespace melon::socket;

void Server::start()
{
  System* sys = Singleton<System>::getInstance();
  sys->init(); 
  std::string root_path = sys->getRootPath();

  IniParser* ini_parser = Singleton<IniParser>::getInstance();
  ini_parser->load(root_path + "/config/server.ini");

  m_ip = (std::string)(*ini_parser)["server"]["ip"];
  m_port = (*ini_parser)["server"]["port"];
  m_threads = (*ini_parser)["server"]["threads"];
  m_max_conns = (*ini_parser)["server"]["max_conns"];
  m_wait_time = (*ini_parser)["server"]["wait_time"];
  m_log_level = (*ini_parser)["server"]["log_level"];

  LogSystem* log_system = Singleton<LogSystem>::getInstance();
  log_system->open(root_path + "/log/server.log");
  log_system->setLevel(m_log_level);
  log_system->setConsole(false);

  TaskDispatcher* dispatcher = Singleton<TaskDispatcher>::getInstance();
  dispatcher->init(m_threads);

  SocketHandler* handler = Singleton<SocketHandler>::getInstance();
  handler->listen(m_ip, m_port);
  handler->handle(m_max_conns, m_wait_time);  
}
