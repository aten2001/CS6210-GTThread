#ifndef __GTTHREAD_INTERNALS_H
#define __GTTHREAD_INTERNALS_H

#include "gtthread_sched.h"		/* For scheduling policy */


typedef long gtthread_lock_t;

/*
 * Threads
 */

typedef struct _gtthread
{
	long sig;			/* Unique signature for this structure */
	gtthread_lock_t lock;		/* Used for internal mutex on structure */
	struct sched_param param;
	struct _gtthread_mutex *mutexes;
	void *exit_value;
	void *(*fun)(void*);		/* Thread start routine */
	void *arg;			/* Argment for thread start routine */
} *gtthread_t;


/*
 * Thread attributes
 */

typedef struct
{
	long sig;			/* Unique signature for this structure */
	gtthread_lock_t lock;		/* Used for internal mutex on structure */
	struct sched_param param;
} ptthread_attr_t;


/*
 * Mutex attributes
 */

typedef struct
{
	long sig;			/* Unique signature for this structure */
} gtthread_mutexattr_t;


/*
 * Mutex variables
 */

typedef struct _gtthread_mutex
{
	long sig;			/* Unique signature for this structure */
	gtthread_lock_t lock;		/* Used for internal mutex on structure */
	gtthread_t owner;		/* Which thread has this mutex locked */
	struct _gtthread_mutex *next, *prev;		/* List of other mutexes he owns */
	struct _pthread_cond *busy;	/* List of condition variables using this mutex */
} gtthread_mutex_t;


/*
 * Condition cariable attributes
 */


typedef struct
{
	long sig;			/* Unique signature for this structure */
} gtthread_cond_t;


/*
 * Condition variables
 */

typedef struct _gtthread_cond
{
	long sig;			/* Unique signature for this structure */
	gtthread_lock_t lock;		/* Used for internal mutex on structure */
	struct _gtthread_mutex *next, *prev;		/* List of condition variables using mutex */
	struct _gtthread_mutex *busy;		/* mutex associated with variable */
} gtthread_cond_t;
