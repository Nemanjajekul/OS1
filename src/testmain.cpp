#include "../lib/console.h"
#include "../lib/hw.h"
#include "../lib/console.h"
uint64 timecount=0;
extern "C" void handlesuprevisortrap()
{
    uint64 scouse;
    __asm__ volatile ("csrr %[scose],scause":[scose]"=r"(scouse));
    if(scouse==(0x01UL <<63 | 0x01))
    {
        timecount++;
        if(timecount>=50)
        {
            __putc('C');
            __putc('\n');
            timecount=0;
        }}
    else
    {
        //__putc('G');
    }
    console_handler();
    __asm__ volatile ("csrc sip,0x02");
}
extern "C" void sprevisortrap();
/*int main()
{
    __asm__ volatile ("csrw stvec, %[vector]"::[vector] "r" (&sprevisortrap));
    __asm__ volatile ("csrs sstatus,0x02");
    __putc('C');
    while(1)
    {

    }
    return 0;
}
.extern _ZN5Riscv20handleSupervisorTrapEv

.align 4
.global _ZN5Riscv14supervisorTrapEv
.type _ZN5Riscv14supervisorTrapEv, @function
_ZN5Riscv14supervisorTrapEv:
    # push all registers to stack
    addi sp, sp, -256
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)
    .endr

    mv a0,sp

    call _ZN5Riscv20handleSupervisorTrapEv

    # pop all registers from stack
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)
    .endr
    addi sp, sp, 256

    sret

*/