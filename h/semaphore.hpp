//
// Created by os on 8/27/24.
//

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include "../h/tcb.hpp"
#include "../h/list.hpp"
extern "C" uint64 copy_and_swapp(uint64 &lock, uint64 expected, uint64 desired);
class Semaphore;
typedef Semaphore* sem_t;
class Semaphore {
    public :
    Semaphore (unsigned short init=1):val(init) { }
    int waitt ();
    int signall ();
    int trywait ();
    int timewait(uint64 time);
    int value () const { return val; }
    protected :
    int block ();
    void unblock ();
    bool gotov=false;
    public:
    int zavrsi();
    private :
    int val;public:
    List<TCB> blocked;
    void bloc(TCB *ccb);
    static Semaphore * createSemaphore(uint64 init);
    //Queue blocked;
} ;



#endif //SEMAPHORE_H
