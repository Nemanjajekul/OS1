//
// Created by marko on 20.4.22..
//

#include "../lib/mem.h"
#include "../h/memory.hpp"
#include "../h/print.hpp"
#include "../h/syscall_c.hpp"
using size_t = decltype(sizeof(0));

void *operator new(size_t n)
{
   // printStringg(" printujemo \n");
  Memory m;
  n=n+1;
 n=n*MEM_BLOCK_SIZE;
   void* a=m.aloc(n);
   return a;
//return __mem_alloc(n);
}

void *operator new[](size_t n)
{
 Memory m;
 n=n+1;
 n=n*MEM_BLOCK_SIZE;
 void* a=m.aloc(n);
 return a;
 //return __mem_alloc(n);

}

void operator delete(void *p) noexcept
{
 /* Memory m;
  m.free(p);*/
mem_free(p);
   //__mem_free(p);
}

void operator delete[](void *p) noexcept
{
   mem_free(p);
   // __mem_free(p);
}