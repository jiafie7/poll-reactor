#include "socket/client_socket.h"
using namespace melon::socket;

#include "utility/system.h"
using namespace melon::utility; 

int main()
{
  System* sys = Singleton<System>::getInstance();
  std::string root_path = sys->getRootPath();

  Singleton<LogSystem>::getInstance()->open(root_path + "/log/client.log");

  ClientSocket client("127.0.0.1", 7777);

  std::string msg = "hi, I am client!";
  
  // 自定义消息格式
  // struct MsgHead msg_head;
  // std::memset(&msg_head, 0, sizeof(msg_head));
  // msg_head.cmd = 1;
  // msg_head.len = msg.size();
  //
  // client.send((char*)&msg_head, sizeof(msg_head));
  //
  client.send(msg.c_str(), msg.size());

  char buf[1024] = {0};
  client.recv(buf, sizeof(buf));
  log_debug("recv: %s", buf);
  
  client.close();
  return 0;
}
