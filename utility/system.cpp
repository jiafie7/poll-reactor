#include "utility/system.h"
using namespace melon::utility;

void System::init()
{ 
  coreDump();
  m_root_path = getRootPath();

  const std::string& dir = m_root_path + "/log";
  DIR* dp = opendir(dir.c_str());

  if (dp == nullptr) 
    ::mkdir(dir.c_str(), 0755); 
  else
    ::closedir(dp);
}   

std::string System::getRootPath()
{
  if (!m_root_path.empty())
    return m_root_path;

  char path[1024] = {0};
  int len = ::readlink("/proc/self/exe", path, 1024);

  if (len < 0 || len >= 1024)
    return "";
  
  for (int i = len; i >= 0; -- i)
    if (path[i] == '/')
    {
      path[i] = '\0';
      break;
    }
  
  len = strlen(path);
  for (int i = len - 1; i >= 0; -- i)
    if (path[i] == '/')
    {
      path[i] = '\0';
      break;
    }
  
  return path;
}
 
void System::coreDump()
{
  struct rlimit x;
  x.rlim_cur = RLIM_INFINITY;
  x.rlim_max = RLIM_INFINITY;
  setrlimit(RLIMIT_CORE, &x);
} 
