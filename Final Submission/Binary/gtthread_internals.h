#ifndef __GTTHREAD_INTERNALS_H
#define __GTTHREAD_INTERNALS_H

#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long gtthread_t;
	
typedef struct _gtthread_descr_struct
{
	struct _gtthread_descr_struct* p_nextlive;		/* Chaining of active threads. */
	struct _gtthread_descr_struct* p_nextwaiting;		/* Next element in the queue holding the thr */
	int p_main;						/* true if main process */
        int p_sigwaiting;					/* true if a sigwait() is in progress */
	int p_terminated;					/* true if terminated e.g. by pthread_exit */
	void* p_retval;						/* placeholder for return value */
	void** p_joining;					/* thread joining on that thread or NULL (Not sure)*/
	gtthread_t p_tid;					/* Thread identifier */
	ucontext_t* p_context;					/* Context switching */
} p_Node;

typedef p_Node* p_Node_ptr;

typedef struct gtthread_mutex_node
{
	long lock;
	gtthread_t owner;
}gtthread_mutex_t;


p_Node* dequeue(p_Node_ptr*);
void add_toQueue(p_Node_ptr*, p_Node*);
p_Node* dequeue_ThreadId(p_Node_ptr*, gtthread_t);
void time_scheduler(int);

#endif
