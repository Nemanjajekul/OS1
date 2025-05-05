#include "../h/memory.hpp"
#include "../h/print.hpp"
#include "../lib/mem.h"
uint32 * Memory::blkend=nullptr;
 uint64 Memory::numblk=0;
 uint32* Memory::blkstart=nullptr;
void Memory::memory_init()
    {
  //align end of mem
    Memory::blkend=(uint32*)(((uint64)HEAP_END_ADDR/MEM_BLOCK_SIZE)*MEM_BLOCK_SIZE);
    Memory::numblk =(uint64)(Memory::blkend-(uint32*)HEAP_START_ADDR)/(MEM_BLOCK_SIZE+sizeof(uint32))-2;

    Memory::blkstart=Memory::blkend-Memory::numblk*MEM_BLOCK_SIZE;
  uint32* start=(uint32*)HEAP_START_ADDR;
  for(uint64 i=0;i<Memory::numblk;i++)
  {
    *(start+i)=0;

  }
  *start=-1*Memory::numblk;
  //*start=Memory::numblk;
  /*uint32 a=4294967295;
 printIntegerr((uint64)*start);
  printStringg(" a \n");
  printIntegerr(-a);
  printStringg(" b \n");
  if(a<0)
    {
    printStringg(" b \n");
    }*/
/*
 printhex((uint64)Memory::blkend);
 printStringg("\n");
  printhex((uint64)HEAP_START_ADDR);
  printStringg("\n");

  printhex((uint64)(Memory::blkend-(uint32*)HEAP_START_ADDR)/(MEM_BLOCK_SIZE*sizeof(uint64)));
  printStringg("\n");
  Memory::numblk =(Memory::blkend-(uint32*)HEAP_START_ADDR)/(MEM_BLOCK_SIZE*sizeof(uint64));
  printhex((uint64)HEAP_START_ADDR);
  printStringg(" heap start\n");
  printhex((uint64)MEM_BLOCK_SIZE);
  printStringg("  blk size\n");
  printhex((uint64)HEAP_END_ADDR);
  printStringg("\n");
  printhex((uint64)Memory::numblk);
  printStringg("  memor blk num\n");
  printhex((uint32)*start);
  printStringg("  start value\n");
  printhex((uint64)blkstart);
  printStringg("  blk start\n");*/
    }
void* Memory::aloc(uint32 size)
    {

  if(size==0)return nullptr;
  size = size / MEM_BLOCK_SIZE + ((size % MEM_BLOCK_SIZE != 0) ? 1 : 0);

uint32 count=0;
  uint32* start=(uint32*)HEAP_START_ADDR;

  while(start<(uint32*)Memory::blkstart && start>=(uint32*)HEAP_START_ADDR)
    {

     if(*start==0)
       {
         printStringg("debelo zeznuo\n");
       return nullptr;
       }
      if(*(start)*-1>=size  && *start>2147483647)
        {
        /*
            {printStringg("  stop it get some help \n\n\n\n\n");*/
        uint32* priv=start;
        priv=start+size  ;
        if((((int)*start)+size )!=0){*priv=*start+size;}
        *start=size ;//}
        uint64 priva=(uint64)Memory::blkstart+(count*MEM_BLOCK_SIZE);

        return (void*)priva;//__mem_alloc(size);////
        }
        else
          {

          if(*start>2147483647)
          {
            count=count+(-*(start));
            start=start+(-*(start));

            }
            else
             {

              count=count+(*(start));
              start=start+(*(start));

              }
                if(start>Memory::blkstart)
                  {
                  return 0;
                  }

          }
          if(start>(uint32*)Memory::blkstart)
            {
              printStringg("   VELIKA GRESKA\n");
            }
    }
    printStringg("   VELIKA GRESKA\n");
    return 0;
  }
int Memory::free(void *ptra)
      {

  uint64 broj=(uint64)ptra-(uint64)Memory::blkstart;
  broj=broj/MEM_BLOCK_SIZE;

    uint32* start=(uint32*)HEAP_START_ADDR;
    start=start+broj;

    uint32* start2=start;

    while(start2>=HEAP_START_ADDR)
     {

      if(start2==HEAP_START_ADDR)
          {
            *start2=-*start;
           if(start2!=start) *start=0;


            return 0;
          }

      if(*start2>0)
        {

        *start=-1*(*start);



        return 0;
        }
        if(*start2>=2147483647)
        {

          *start2=*start2-*start;
            *start=0;



            return 0;
        }

      start2--;
      }
          printStringg("  velika greska\n");
  return -1;
  }
  //2264933376
  //2264933120