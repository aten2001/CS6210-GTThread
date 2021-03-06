#include "gtthread.h"
#include "gtthread_sched.h"
gtthread_t lastThreadId = 0; 
sigset_t signal_Mask;
static bool initialized = false;
p_Node* currentThread = NULL;
p_Node_ptr ready_queue = NULL;
p_Node_ptr terminated_queue = NULL;
p_Node_ptr waiting_queue = NULL; 
static p_Node* new_GTThreadNode()
{
	p_Node* new_Node = (p_Node*)malloc(sizeof(p_Node));
	
	if(!new_Node)
	{
		printf("Error trying to create a new node!\n");
		return NULL;
	}
	new_Node->p_tid = ++lastThreadId;
	new_Node->p_context = NULL;
	new_Node->p_main = 0;
    	new_Node->p_sigwaiting = 0; 	
	new_Node->p_nextlive = NULL;
	new_Node->p_nextwaiting = NULL;
	return new_Node;
}

static void freeThreadNode(p_Node* threadNode)
{
	if(!threadNode)
	{
		printf("The thread node to be freed is empty.\n");
		return;
	}
	if(!(threadNode->p_main))
		free(threadNode->p_context->uc_stack.ss_sp);
	free(threadNode->p_context);
	free(threadNode);
}	

void gtthread_init(long period)
{
	p_Node* new_Node = NULL;
	init_Scheduler();
	new_Node = new_GTThreadNode();
	if(!new_Node)
	{
		printf("gtthread_init() Error: Unable to create main.\n");
		exit(1);
	}
	make_MainContext(new_Node);
	new_Node->p_main  = 1;
	currentThread = new_Node;
	sigemptyset(&signal_Mask);
	sigaddset(&signal_Mask,SIGNAL_TYPE);
	init_Itimerval(period);
	init_Sigtimer();
	initialized = true;
}

int gtthread_create(gtthread_t *thread, void *(*start_routine)(void *), void *arg)
{
	p_Node* new_Node = NULL;
	sigprocmask(SIG_BLOCK, &signal_Mask, NULL);
	if(!initialized)
	{
		printf("gtthread_create() Failed: gtthread_init() not called.");
		sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);		
		return(-1);
	}
	if((!start_routine) || (!thread))
	{
		printf("gtthread_create() Failed: Check Arguments.\n");
		sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);		
		return -1;
	}	
	new_Node = new_GTThreadNode();
	if(!new_Node)
	{
		printf("gtthread_create() Failed: Cannot create Node.\n");
		sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
		return -1;
	}
	make_ThreadContext(new_Node,thread, start_routine, arg);
	*thread = new_Node->p_tid;
	add_toQueue(&ready_queue, new_Node);
	sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
	return 0;
}

gtthread_t gtthread_self(void)
{
	return currentThread->p_tid;	
}

int gtthread_equal(gtthread_t t1, gtthread_t t2) 
{
   	if(t1 == t2)
		return 1;
        else
		return 0;
}

static p_Node* findThreadNode(gtthread_t thread)
{
	p_Node_ptr threadList;
	p_Node* tempIterator = NULL;
	if(ready_queue)
	{
		threadList=ready_queue;
		tempIterator = threadList->p_nextlive;
		do
		{
			if(tempIterator->p_tid == thread)
			{
				return tempIterator;
			}
			tempIterator = tempIterator->p_nextlive;
		}while(tempIterator != threadList->p_nextlive);
	}
	if(waiting_queue)
	{
		threadList=waiting_queue;
		tempIterator = NULL;
		tempIterator = threadList->p_nextlive;
		do
		{
			if(tempIterator->p_tid == thread)
			{
				return tempIterator;
			}
			tempIterator = tempIterator->p_nextlive;
		}while(tempIterator != threadList->p_nextlive);
	}
	return NULL;
}

int  gtthread_join(gtthread_t thread, void **status)
{
	p_Node* joining_Thread = NULL;
	sigprocmask(SIG_BLOCK, &signal_Mask, NULL);
	joining_Thread = findThreadNode(thread);
	if(joining_Thread)
	{
		if(joining_Thread->p_nextwaiting)
		{
			sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);			
			return -1;
		}
		joining_Thread->p_nextwaiting = currentThread;
		currentThread->p_joining = status;
		currentThread->p_sigwaiting = 1;
		add_toQueue(&waiting_queue, currentThread);
		sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
		raise(SIGNAL_TYPE);
	}		
	else
	{
		joining_Thread = dequeue_ThreadId(&terminated_queue, thread);
		if(joining_Thread)
		{
			if(joining_Thread->p_nextwaiting)
			{
				sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
				return -1;
			}
			if(status)
			{
				*status = joining_Thread->p_retval;
			}
			freeThreadNode(joining_Thread);
		}
		else
		{
			printf("Thread not found.\n");
			sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
			return -1;
		}
	}
	sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
	return 0;
}
	

void gtthread_exit(void *retval)
{
	p_Node* tempWaitingThread = NULL;
	sigprocmask(SIG_BLOCK, &signal_Mask, NULL);
	/*printf("Cancel: removing thread %lu with context %ld\n",currentThread->p_tid, currentThread->p_context->uc_stack.ss_sp); */
	currentThread->p_retval = retval;
	currentThread->p_terminated = 1;	
	if(currentThread->p_nextwaiting)
	{	
		if((currentThread->p_nextwaiting)->p_joining)
		{
			*((currentThread->p_nextwaiting)->p_joining) = currentThread->p_retval;	
		}		
		(currentThread->p_nextwaiting)->p_sigwaiting = 0;
		tempWaitingThread = dequeue_ThreadId(&waiting_queue, (currentThread->p_nextwaiting)->p_tid);
		if(!tempWaitingThread)
		{
			printf("Dequeue by ID failed.\n");
		}
		add_toQueue(&ready_queue, tempWaitingThread);
	}	
	add_toQueue(&terminated_queue, currentThread);
	sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
	raise(SIGNAL_TYPE);
}

p_Node* dequeue_ThreadId(p_Node_ptr* list_Thread, gtthread_t thread)
{
	p_Node* dequeue_thread = NULL;
	p_Node* temp = NULL;
	p_Node* prev_Node = NULL;
	if(!(*list_Thread))
	{
		return NULL;
	}
	if((*list_Thread)->p_nextlive == (*list_Thread))
	{
		if((*list_Thread)->p_tid == thread)
		{
			dequeue_thread = *list_Thread;
			*list_Thread = NULL;
		}
		else
		{
			dequeue_thread = NULL;	
		}
	}
	else
	{
		temp = (*list_Thread)->p_nextlive;
		prev_Node = (*list_Thread);
		do
		{
			if(temp->p_tid == thread)
			{
				dequeue_thread = temp;
				prev_Node->p_nextlive = temp->p_nextlive;
				if(temp == (*list_Thread))	
					*list_Thread = prev_Node;	
				break;
			}
			prev_Node = temp;
			temp = temp->p_nextlive;
		}while(temp != (*list_Thread)->p_nextlive);
			
	}	
	dequeue_thread->p_nextlive = NULL;
	return dequeue_thread;
}

void add_toQueue(p_Node_ptr* ThreadQueue, p_Node* nodeToInsert)
{
	if(!nodeToInsert)
	{
		printf("add_toQueue() Error: No node to Insert.\n");
		return;
	}
	if(!(*ThreadQueue))
	{
		*ThreadQueue = nodeToInsert;
		(*ThreadQueue)->p_nextlive = nodeToInsert;
		return;
	}
	nodeToInsert->p_nextlive = (*ThreadQueue)->p_nextlive;
        (*ThreadQueue)->p_nextlive = nodeToInsert;
	*ThreadQueue = nodeToInsert;
}

int gtthread_yield(void)
{
	raise(SIGNAL_TYPE);
	return 0;
}

int  gtthread_cancel(gtthread_t thread)
{
	p_Node* cancel_Thread = NULL; 
	p_Node* tempWaitingThread = NULL;
	sigprocmask(SIG_BLOCK, &signal_Mask, NULL);
	cancel_Thread = dequeue_ThreadId(&ready_queue, thread);
	if(!cancel_Thread)
		cancel_Thread = dequeue_ThreadId(&waiting_queue, thread);
	if(!cancel_Thread)
	{
		printf("gtthread_cancel() Error: Node not found in ready or waiting queue.\n");
		sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
		return -1;
	}
	cancel_Thread->p_retval = NULL;	
	cancel_Thread->p_terminated = 1;	
	if(cancel_Thread->p_nextwaiting)
	{	
		if((cancel_Thread->p_nextwaiting)->p_joining)
			*((cancel_Thread->p_nextwaiting)->p_joining) = cancel_Thread->p_retval;
		(cancel_Thread->p_nextwaiting)->p_sigwaiting = 0;
		tempWaitingThread = dequeue_ThreadId(&waiting_queue, (cancel_Thread->p_nextwaiting)->p_tid);
		add_toQueue(&ready_queue, tempWaitingThread);
	}	
	add_toQueue(&terminated_queue, cancel_Thread );
	sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
	return 0;	
}
