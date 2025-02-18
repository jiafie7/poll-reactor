#include "thread/thread_pool.h"

using namespace melon::thread;

void ThreadPool::create(int threads)
{
  AutoLock lock(&m_mutex);
  for (int i = 0; i < threads; ++ i)
  {
    WorkerThread* thread = new WorkerThread();
    m_pool.push_back(thread);
    thread->start();
  }
  m_threads = threads;
  log_debug("thread pool create worker threads: %d", threads);
}

WorkerThread* ThreadPool::get()
{
  AutoLock lock(&m_mutex);

  while (m_pool.empty())
    m_cond.wait(&m_mutex);

  WorkerThread* thread = m_pool.front();
  m_pool.pop_front();

  return thread;
}

void ThreadPool::put(WorkerThread* thread)
{
  AutoLock lock(&m_mutex);

  m_pool.push_back(thread);

  m_cond.signal();
}

void ThreadPool::assign(Task* task)
{
  WorkerThread* thread = get();
  thread->assign(task);
}

bool ThreadPool::empty()
{
  AutoLock lock(&m_mutex);

  return m_pool.empty();
}

