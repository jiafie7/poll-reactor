#pragma once

#include <list>

#include "thread/auto_lock.h"
#include "thread/worker_thread.h"
using namespace melon::thread;

#include "utility/singleton.h"
using namespace melon::utility;

namespace melon
{
  namespace thread
  {
    class ThreadPool
    {
      SINGLETON(ThreadPool);
    public:   
      void create(int threads);

      WorkerThread* get();
      void put(WorkerThread* thread);
      
      void assign(Task* task);
      bool empty();

    private:
      int m_threads = 0;
      Mutex m_mutex;
      Condition m_cond;
      std::list<WorkerThread*> m_pool;
    };
  }
}
