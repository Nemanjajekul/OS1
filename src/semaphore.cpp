//
// Created by os on 8/27/24.
//

#include "../h/semaphore.hpp"
#include "../h/print.hpp"
uint64 locksem = 0;
#define LOCK() {}//while(copy_and_swapp(locksem, 0, 1)) TCB::dispatch()
#define UNLOCK(){}// while(copy_and_swapp(locksem, 1, 0))
int Semaphore::waitt()
{
  LOCK();

if (--val<0) block();
UNLOCK();
return 0;
}
int Semaphore::trywait()
    {
  LOCK();
  if(gotov==true)
  {
    return -1;
  }
  if (--val<0) return 0;
  if(gotov==true)
  {
    return -1;
  }
  UNLOCK();
  return 1;
  }
int Semaphore::signall(){

LOCK();
  if(gotov==true)
  {
    return -1;
  }
if(++val<=0) unblock() ;
UNLOCK();
return 0;
  }
void Semaphore::bloc(TCB *old)
      {
  blocked.addLast(old);
  }
int Semaphore::block ()
      {
  LOCK();
    TCB *old = TCB::running;

    bloc(old);
    TCB::running = Scheduler::get();

    TCB::contextSwitch(&old->context, &TCB::running->context);


      UNLOCK();
      return 0;
  }
void Semaphore::unblock ()
      {
  LOCK();
  TCB* t = blocked.removeFirst() ;
    Scheduler::put(t);
    UNLOCK();
  }

Semaphore* Semaphore::createSemaphore(uint64 init)
      {
  LOCK();
 return new Semaphore(init);
  UNLOCK();
  }
  int Semaphore::zavrsi()
      {gotov=true;
  LOCK();
    while(!blocked.peekFirst())
      {
      printStringg("   VELIKA GRESKA\n");
      TCB *old = TCB::running;
      //if (!old->isFinished()) { blocked.addLast(old); }
      TCB::running = blocked.removeLast();

      TCB::contextSwitch(&old->context, &TCB::running->context);
      }
  UNLOCK();
  return 0;
    }
    int timewait(uint64 time)
        {
      return 1;
      }