#pragma once

namespace melon
{
  namespace thread
  {
    class Task
    {
    public:
      Task();
      Task(void* data);
      virtual ~Task(); 

      void* getData();
      void setData(void* data);

      virtual void run() = 0; 
      virtual void destroy() = 0; 

    protected:
      void* m_data;     
    };
  }
}
