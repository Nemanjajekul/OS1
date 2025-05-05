//
// Created by os on 8/23/24.
//

#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.hpp"
/*void * ::operator new(size_t) {
  void* temp=nullptr;
  return temp;
}
void ::operator delete (void*) noexcept
    {

  }*/
Thread::Thread (void (*body)(void*), void* arg)
{
  thread_create(&myHandle,body,arg);
  }
 Thread::~Thread ()
{
  }
int Thread::start ()
{
  thread_create(&myHandle,wrap,this);
  return 0;
}
 void Thread::dispatch ()
{
thread_dispatch();
}

 int Thread::sleep (time_t a)
{
   time_sleep(a);
   return 0;
  }
Thread::Thread ()
{
  myHandle=nullptr;
    body=nullptr;
    arg=nullptr;
  }

Semaphore::Semaphore (unsigned int init)
{
  sem_open(&myHandle,init);
  }

  Semaphore::~Semaphore ()
{
    sem_close(myHandle);
  }

int Semaphore::wait ()
{
  return sem_wait(myHandle);
 // return 0;
  }

int Semaphore::signal ()
{
  return sem_signal(myHandle);
  return 0;
  }

int Semaphore::timedWait (time_t t)
{
  return sem_timedwait(myHandle,t);
  return 0;
  }

int Semaphore::tryWait()
{
  return sem_trywait(myHandle);
  return 0;
  }
void PeriodicThread::terminate ()
{
  }
PeriodicThread::PeriodicThread (time_t period)
{
  }

char Console::getc ()
{
  return '0';
  }

 void Console::putc (char)
{
  }





