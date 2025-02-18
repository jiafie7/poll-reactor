#include "thread/task.h" 

using namespace melon::thread;

Task::Task()
  : m_data(nullptr)
{}

Task::Task(void* data)
  : m_data(data)
{}

Task::~Task()
{
  m_data = nullptr;
}

void* Task::getData()
{
  return m_data;
}

void Task::setData(void* data)
{
  m_data = data;
}
