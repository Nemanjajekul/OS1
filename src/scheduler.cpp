//
// Created by marko on 20.4.22..
//

#include "../h/scheduler.hpp"
#include "../h/tcb.hpp"
#include "../h/print.hpp"
List<TCB> Scheduler::readyThreadQueue;
List<TCB> Scheduler::slepy;


TCB *Scheduler::get()
{
    return readyThreadQueue.removeFirst();
}

void Scheduler::put(TCB *ccb)
{
    readyThreadQueue.addLast(ccb);
}

void Scheduler::updateee()
{// printStringg(" s\n");
  if(Scheduler::slepy.peekFirst()==0){return ;}
  List<TCB>::Elem * travel=Scheduler::slepy.head;
  List<TCB>::Elem * prev=nullptr;
bool ishead=true;
bool headchanged=true;
  while(travel)
    {

    /* printIntegerr((uint64)travel->data->slepy);
      printStringg("\n");*/
    headchanged=false;
    if(travel->data->slepy!=0)
travel->data->slepy=travel->data->slepy-1;
    if(travel->data->slepy==0)
      {// printStringg(" imfiltrirano\n\n\n");
      Scheduler::put(travel->data);
      if(ishead)
        {
        Scheduler::slepy.head=travel->next;
        delete travel;
        travel=Scheduler::slepy.head;
        headchanged=true;
         if (!Scheduler::slepy.head) { Scheduler::slepy.tail = 0; }
        }
        else
          {
           // Scheduler::put(travel->data);
            prev->next=travel->next;
            delete travel;
            travel=prev->next;
            if(!travel)
              {
              Scheduler::slepy.tail=prev;
              }
          }
      }
      else
        {
        prev=travel;
        travel=travel->next;
        }
        ishead=false;
      if(headchanged)
      {ishead=true;}

      headchanged=false;
      //prev=travel;
     /* if(travel->next)
      {travel=travel->next;}
      else
        {
        break;
        }*/
    }
   // return nullptr;// readyThreadQueue.removeFirst();
}

void Scheduler::put_slepy(TCB *ccb)
{
  slepy.addLast(ccb);

}