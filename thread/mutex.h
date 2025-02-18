#pragma once

#include <pthread.h>

namespace melon
{
  namespace thread
  {
    class Mutex
    {
      friend class Condition;
    public:
      Mutex();
      ~Mutex();

      void lock();
      bool tryLock();
      void unlock();

    private:
      pthread_mutex_t m_mutex;
    };
  }
}
