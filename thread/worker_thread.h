#pragma once

#include <signal.h>  // sigset_t, sigfillset(), sigprocmask()

#include "thread/condition.h"
#include "thread/mutex.h"
#include "thread/task.h"
#include "thread/thread.h"

#include "utility/log_system.h"
using namespace melon::utility;

namespace melon
{
  namespace thread
  {
    class WorkerThread : public Thread
    {
    public:
      WorkerThread();
      ~WorkerThread();

      virtual void run(); 
      void assign(Task* task);
      static void cleanup(void* ptr);

    private:
      Task*     m_task;
      Mutex     m_mutex;
      Condition m_cond;
    };
  }
}
