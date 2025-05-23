//
// Created by os on 8/23/24.
//

#ifndef SYSCALL_C_H
#define SYSCALL_C_H
#include "../lib/hw.h"
#include "../h/print.hpp"
void* mem_alloc(size_t size);

int mem_free(void*);

class _thread;
typedef _thread* thread_t;

int thread_create(thread_t* handle, void(*start_routine)(void*),void* arg);

int thread_exit();

void thread_dispatch();

class _sem;
typedef _sem* sem_t;

int sem_open(sem_t* handle, unsigned init);

int sem_close(sem_t handle);

int sem_wait(sem_t id);

int sem_signal(sem_t id);

int sem_timedwait(sem_t id, time_t timeout);

int sem_trywait(sem_t id);

int time_sleep (time_t);

extern const int EOF;
char getc ();

void putc (char);

#endif //SYSCALL_C_H
