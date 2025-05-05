//
// Created by marko on 20.4.22..
//

#include "../h/tcb.hpp"
#include "../h/workers.hpp"
#include "../h/print.hpp"
#include "../h/riscv.hpp"
#include "../h/memory.hpp"
extern void userMain();
void wrapermain(void*)
    {
  userMain();
  }
int main()
{
  Memory m;//,k;
  m.memory_init();

 //void* a1=m.aloc(100);
//  k.aloc(3);
  /*printhex((uint64)a1);
     printStringg(" lat1 \n\n");
  //m.free(a1);
  uint64 lat2=(uint64)k.aloc(1);
  printhex((uint64)lat2);
        printStringg(" lat2 \n\n");
    m.aloc(3);
    k.aloc(5);
    k.free((void*)lat2);
    m.aloc(1);
    m.aloc(3);
    return 0;*/
  /*void* a1=m.aloc(532);
  printIntegerr((uint64)a1);
        printStringg("  a1 \n");
        m.free(a1);
         void* a2=m.aloc(532);
          printIntegerr((uint64)a2);
        printStringg("  a2\n");*/
    TCB *threads[15];
    //List<TCB>test;

/*for(int i=0;i<80;i++)
  {
  threads[i] = TCB::createThread(nullptr,nullptr);
  }*/
   threads[0] = TCB::createThread(nullptr,nullptr);
    TCB::running = threads[0];

Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
 threads[1] = TCB::createThread(wrapermain,nullptr);
     /*threads[1] = TCB::createThread(workerBodyA,nullptr);
   printStringg("ThreadA created\n");
    threads[2] = TCB::createThread(workerBodyB,nullptr);
    printStringg("ThreadB created\n");
    threads[3] = TCB::createThread(workerBodyC,nullptr);
    printStringg("ThreadC created\n");
    threads[4] = TCB::createThread(workerBodyD,nullptr);
    printStringg("ThreadD created\n");*/


    printStringg("dosao");
  while (!threads[1]->isFinished() )
    {
   // printStringg("dosao");
        TCB::yield();
    }
  /*while (!threads[1]->isFinished() && !threads[2]->isFinished() && !threads[3]->isFinished() && !threads[4]->isFinished() )
    {
        TCB::yield();
    }*/
   /* for (auto &thread: threads)
    {
        delete thread;
    }
    printString("Finished\n");
*/
    return 0;
}
