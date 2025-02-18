#pragma once

#include <list>
#include "thread/task.h"
#include "thread/thread.h"
#include "thread/thread_pool.h"

namespace melon
{
  namespace thread
  {
    class TaskDispatcher : public Thread
    {
      SINGLETON(TaskDispatcher);
    public:
      void init(int threads);

      void push(Task* task);

      void handle(Task* task);
      bool empty();

      virtual void run();

    private:
      std::list<Task*>  m_queue;
      Mutex             m_mutex;
      Condition         m_cond;
    };
  }
}
