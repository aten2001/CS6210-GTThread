#ifndef __GTTHREAD_SCHED_H
#define __GTTHREAD_SCHED_H

#include <signal.h>
#include "gtthread_internals.h"
#include <sys/time.h>
#include <string.h>
#define SIGNAL_TYPE SIGVTALRM


void init_Itimerval(long period);
void init_Scheduler();
void init_Sigtimer();
int make_ThreadContext(p_Node* new_Node,gtthread_t *thread, void *(*start_routine)(void *), void *arg);
void make_MainContext(p_Node* node);
void time_scheduler(int sigNum);
p_Node * dequeue(p_Node_ptr*);
void gtthread_exit(void *retval);

extern struct itimerval quantum;
extern struct sigaction signal_Scheduler;
extern sigset_t signal_Mask; 
extern p_Node* currentThread;
extern p_Node_ptr ready_queue;
extern p_Node_ptr terminated_queue;
extern p_Node_ptr waiting_queue; 

#endif /* __GTTHREAD_SCHED_H */
