#include "gtthread_sched.h"
#define TIME 1000000
#define TIMER_TYPE ITIMER_VIRTUAL
#define STACK_SIZE 8*1024
struct itimerval quantum;
struct sigaction signal_Scheduler;
void init_Itimerval(long period)
{
	long sec = 0;
	long usec = 0;
	if(period <= 0)
	{
		printf("gtthread_init() Error: Period cannot be lesser than zero(0).\n");
		exit(1);
	}
	sec = period/TIME;
	usec = period % TIME;
	quantum.it_interval.tv_sec = sec;
	quantum.it_interval.tv_usec = usec;
	quantum.it_value.tv_sec = sec;
	quantum.it_value.tv_usec = usec;
}

void init_Scheduler()
{
	sigemptyset(&signal_Scheduler.sa_mask);
	signal_Scheduler.sa_flags = 0;
	signal_Scheduler.sa_handler = time_scheduler;
	sigaction(SIGNAL_TYPE, &signal_Scheduler, NULL);
}

void init_Sigtimer()
{
	if(setitimer(TIMER_TYPE, &quantum, NULL)==0)
	{
		/* printf("Timer initialized\n"); */
	}
	else
	{
		printf("An Error occured while initializing timer.\n");
		exit(-1);
	}
}

static void thread_Control(void *(*start_routine)(void *), void *arg)
{
	void* returnValue = NULL;
	sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
	returnValue = start_routine(arg);
	gtthread_exit(returnValue);
}


int make_ThreadContext(p_Node* new_Node,gtthread_t *thread, void *(*start_routine)(void *), void *arg)
{
	new_Node->p_context = (ucontext_t*)malloc(sizeof(ucontext_t));
	if(!(new_Node->p_context))
	{
		free(new_Node);
		printf("gtthread_create() Error: Couldn't allocate space for new \n");
		sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
		return -1;
	}
	getcontext(new_Node->p_context);
	new_Node->p_context->uc_stack.ss_sp = malloc(STACK_SIZE);
	if(new_Node->p_context->uc_stack.ss_sp == NULL)
	{
		free(new_Node->p_context);
		free(new_Node);
		printf("\ngtthread_create() : FAILED on stack memory allocation\n");
		sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
		return -1;
	}
	new_Node->p_context->uc_link = NULL;
	new_Node->p_context->uc_stack.ss_flags = 0;
	new_Node->p_context->uc_stack.ss_size = STACK_SIZE;
	makecontext(new_Node->p_context, (void (*) (void))thread_Control, 2, start_routine, arg);
	return 0;
}


void make_MainContext(p_Node* node)
{
	node->p_context = (ucontext_t*) malloc(sizeof(ucontext_t));
	if(!(node->p_context)) 
	{
		free(node);
		printf("gtthread_init() Error: Unable to allocate space for main's context.\n");
		exit(1);
	}
	getcontext(node->p_context);
	node->p_context->uc_stack.ss_flags = 0;
	node->p_context->uc_link = NULL;
}

p_Node* dequeue(p_Node_ptr* Queue)
{
   	p_Node* returnNode = NULL;
	if(!(*Queue))
	{
		return NULL;
	}
	if((*Queue)->p_nextlive == *Queue)
        {
      		returnNode = *Queue;
        	*Queue = NULL;
    	}
	else
	{
		returnNode = (*Queue)->p_nextlive;
        	(*Queue)->p_nextlive = (*Queue)->p_nextlive->p_nextlive;
    	}
	return returnNode;
}

void time_scheduler(int sigNum)
{
	p_Node* candidate = NULL;
	sigprocmask(SIG_BLOCK, &signal_Mask, NULL);	
	candidate = dequeue(&ready_queue);
	if(!candidate)
	{
		if(currentThread->p_sigwaiting)
		{		
			printf("Error: No Running Thread in ready queue..\n");
			exit(1);
		}
		if(!(currentThread->p_terminated))
		{
			setitimer(TIMER_TYPE, &quantum, NULL);
			sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
			return;
		}
		else
		{
			sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
			exit(0);
		}
	}
	else
	{
		if(currentThread->p_terminated)
		{	
			currentThread = candidate;
			setitimer(TIMER_TYPE, &quantum, NULL);
			sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
			setcontext(currentThread->p_context);
		}
		else if(currentThread->p_sigwaiting)
		{
			currentThread = candidate;
			setitimer(TIMER_TYPE, &quantum, NULL);
			sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
			swapcontext(waiting_queue->p_context, currentThread->p_context);	
		}
		else
		{	
			add_toQueue(&ready_queue, currentThread);
			currentThread = candidate;
			setitimer(TIMER_TYPE, &quantum, NULL);
			sigprocmask(SIG_UNBLOCK, &signal_Mask, NULL);
			swapcontext(ready_queue->p_context, currentThread->p_context);
		}
	}
}

