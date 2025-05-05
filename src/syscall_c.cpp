//
// Created by os on 8/23/24.
//
#include "../h/syscall_c.hpp"
#include "../h/print.hpp"
#include "../h/memory.hpp"
void* mem_alloc(size_t size)
{
  __asm__ volatile("mv a1,a0; li a0,0x01;ecall");
uint64 ret;
__asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
return (void*)ret;
 /*Memory m;
 return m.aloc(size);*/
  }

int mem_free (void* ptr)
{
  __asm__ volatile("mv a1,a0; li a0,0x02;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
  /*Memory m;
 return m.free(ptr);*/
  return 0;
}

 int thread_create (thread_t* handle,void(*start_routine)(void*),void* arg)
{//
  __asm__ volatile("mv a3,a2;mv a2,a1;mv a1,a0; li a0,0x11;ecall");

  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

int thread_exit ()
{
  __asm__ volatile(" li a0,0x12;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

void thread_dispatch ()
{
  __asm__ volatile("li a0,0x13;ecall");

}

int sem_open (sem_t* handle,unsigned init)
{
  __asm__ volatile("mv a2,a1;mv a1,a0; li a0,0x21;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

int sem_close (sem_t handle)
{
  __asm__ volatile("mv a1,a0; li a0,0x22;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}


int sem_wait (sem_t id)
{
  __asm__ volatile("mv a1,a0; li a0,0x23;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

int sem_signal (sem_t id)
{
  __asm__ volatile("mv a1,a0; li a0,0x24;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

int sem_timedwait(sem_t id,time_t timeout)
{
  __asm__ volatile("mv a2,a1;mv a1,a0; li a0,0x25;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

int sem_trywait(sem_t id)
{
  __asm__ volatile("mv a1,a0; li a0,0x26;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

int time_sleep (time_t a)
{
  __asm__ volatile("mv a3,a2;mv a2,a1;mv a1,a0; li a0,0x31;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;
}

char getc ()
{
  __asm__ volatile(" li a0,0x41;ecall");
  uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return (char)ret;
}

void putc (char)
{
  __asm__ volatile("mv a1,a0; li a0,0x42;ecall");
  /*uint64 ret;
  __asm__ volatile("mv %[ret],a0":[ret]"=r" (ret));
  return ret;*/
}


