//
// Created by marko on 20.4.22..
//

#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../h/memory.hpp"
#include "../lib/console.h"
#include "../h/print.hpp"
#include "../h/semaphore.hpp"
#include "../h/scheduler.hpp"
void Riscv::popSppSpie()
{
    __asm__ volatile("csrw sepc, ra");
   mc_sstatus(SSTATUS_SPP);
    __asm__ volatile("sret");
}

void Riscv::handleSupervisorTrap(registers* p)
{        uint64 volatile sepc ;
        uint64 volatile sstatus ;

    uint64 scause = r_scause();
    sstatus = r_sstatus();
    sepc = r_sepc();
    char b='0';
    //char *c=nullptr;
    if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL)
    {

      // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)

        switch(p->a0)
          {
          case 0x01://aloc
              Memory m;
              p->a0=(uint64)m.aloc(p->a1);
            break;
        case 0x02://free
            Memory t;
            t.free((void*)p->a1);
            break;
        case 0x11://thred_crate
            *(uint64*)(p->a1)=(uint64)TCB::createThread((TCB::Body)p->a2,(void*)p->a3);
            if((uint64*)p->a1==0)
              {
              p->a0=-1;
              }
              else
                {
                p->a0=0;
                }
            break;
        case 0x12://thred_exit
            TCB::running->setFinished(true);
            p->a0=0;
            TCB::dispatch();
            break;
        case 0x13://thred_dispache
            sepc=r_sepc();
            sstatus=r_sstatus();
            TCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
            break;

        case 0x21://sem_open
            *(uint64*)(p->a1)=(uint64)Semaphore::createSemaphore((uint64)p->a2);
            if((uint64*)p->a1==0)
            {
                p->a0=-1;
            }
            else
            {
                p->a0=0;
            }
            break;

        case 0x22://sem_close
            p->a0=((Semaphore*)(p->a1))->zavrsi();
            break;

        case 0x23://sem_wait
            p->a0=((Semaphore*)(p->a1))->waitt();
            break;

        case 0x24://sem_signal
            p->a0=((Semaphore*)(p->a1))->signall();
            break;

        case 0x25://sem_timedwait

            break;

        case 0x26://try_wait
            p->a0=((Semaphore*)(p->a1))->trywait();
            break;

        case 0x31://time_sleep
            p->a0=TCB::slep(p->a1);
            break;

        case 0x41://getc

            b=__getc();
            b=b;
           // p->a1=p->a0;
           // c=&b;
           // printStringg(c);
            //printStringg(" \n getujem c \n");
            __putc(b);
            p->a0=b;
            break;
        case 0x42://putc
            __putc((char)p->a1);

            //printStringg(" putujem c \n");
            break;
          }
          w_sepc(sepc+4);
            w_sstatus(sstatus);
       /* TCB::timeSliceCounter = 0;
        TCB::dispatch();
        w_sstatus(sstatus);
        w_sepc(sepc);*/
    }
    else if (scause == 0x8000000000000001UL)
    {
        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)

       /* sepc = r_sepc();
            sstatus = r_sstatus();*/
        Scheduler::updateee();
       /* w_sstatus(sstatus);
            w_sepc(sepc);*/
        // printStringg("time\n");
        TCB::timeSliceCounter++;
        if (TCB::timeSliceCounter >= TCB::running->getTimeSlice())
        {
            sepc = r_sepc();
            sstatus = r_sstatus();
            TCB::timeSliceCounter = 0;
            TCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
        }mc_sip(SIP_SSIP);
    }
    else if (scause == 0x8000000000000009UL)
    {
        // interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
        console_handler();
    }
    else
    {
      printhex(sstatus);
      printStringg(" sstatus \n");
      printhex(sepc);
        printStringg(" sepc \n");
        printhex(r_stval());
        printStringg(" stval \n");
        printhex(scause);
        printStringg(" scause \n");
        uint32 end = 0x5555;
        uint32* end_addr = (uint32*) 0x100000;
        *end_addr = end;
        // unexpected trap cause
    }
}