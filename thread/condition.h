#pragma once

#include <pthread.h>
#include "thread/mutex.h"

namespace melon
{
  namespace thread
  {
    class Condition
    {
    public:
      Condition();
      ~Condition();

      void wait(Mutex* mutex);
      void signal();
      void broadcast();
      
    private:
      pthread_cond_t m_cond;
    };
  }
}
