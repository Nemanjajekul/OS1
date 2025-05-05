
#ifndef MEMORY_HPP
#define MEMORY_HPP
#include "../lib/hw.h"

class Memory
  {
  public:
void memory_init();
void* aloc(uint32 size);
int free(void *ptr);
  static uint32 * blkend;
  static uint64 numblk;
  static uint32* blkstart;
};
#endif //MEMORY_H
