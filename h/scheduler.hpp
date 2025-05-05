//
// Created by marko on 20.4.22..
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SCHEDULER_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SCHEDULER_HPP

#include "list.hpp"
#include "../lib/hw.h"
class TCB;

class Scheduler
{
private:
    static List<TCB> readyThreadQueue;

    static List<TCB> slepy;

public:
    static TCB *get();

    static void put(TCB *ccb);

    static void updateee();

    static void put_slepy(TCB *ccb);

};

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SCHEDULER_HPP
