//
// Created by marko on 20.4.22..
//

#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/print.hpp"
TCB *TCB::running = nullptr;

uint64 TCB::timeSliceCounter = 0;

TCB *TCB::createThread(Body body,void* arg)
{
   // printStringg(" AAAAAA \n\n\n\n");
    return new TCB(body, TIME_SLICE,arg);
}

void TCB::yield()
{
    __asm__ volatile ("li a0,0x13;ecall");
}

void TCB::dispatch()
{
    TCB *old = running;
    if (!old->isFinished()) { Scheduler::put(old); }
    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::threadWrapper()
{
    Riscv::popSppSpie();
    running->body(running->arg);
    running->setFinished(true);
    TCB::yield();
}
int TCB::slep(uint64 time)
    {
       TCB *old = running;
       running->slepy=time;
    if (!old->isFinished()) { Scheduler::put_slepy(old); }
    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
    return 0;
  }