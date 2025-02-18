#include <thread/worker_thread.h>
#include <thread/thread_pool.h>

using namespace melon::thread;

WorkerThread::WorkerThread()
  : Thread()
  , m_task(nullptr)
{
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::run()
{
  sigset_t mask;
  if (sigfillset(&mask) != 0)
  {
    log_error("worker thread sigfillset error!");
    return;
  }
  if (pthread_sigmask(SIG_SETMASK, &mask, nullptr) != 0)
  {
    log_error("worker thread pthread_sigmask error!");
    return;
  }

  pthread_cleanup_push(cleanup, this);
  while (true)
  {
    m_mutex.lock();
    while (m_task == nullptr)
    {
      m_cond.wait(&m_mutex);
    }

    m_mutex.unlock();

    int rc = 0;
    int old_state = 0;
    rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);

    m_task->run();

    m_task->destroy();
    m_task = nullptr; 

    Singleton<ThreadPool>::getInstance()->put(this);
    
    rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_state);
    pthread_testcancel();
  }

  pthread_cleanup_pop(1);
}

void WorkerThread::assign(Task* task)
{
  m_mutex.lock();

  m_task = task;

  m_cond.signal();
  m_mutex.unlock();
}
 
void WorkerThread::cleanup(void* ptr)
{
  log_debug("worker thread cleanup handler: %x.", ptr);
}
