/*
  Test 5a
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/

#include <stdio.h>
#include <gtthread.h>

#define NUM_THREADS 100

gtthread_mutex_t g_mutex;
int g_num = 0;

void* worker(void* arg)
{
	gtthread_mutex_lock(&g_mutex);
	printf("Mutex Lock obtained by: %lu\n", gtthread_self());
	gtthread_mutex_unlock(&g_mutex);	
    return NULL;
}

int main()
{
	printf(" Tests mutexes\n");
    printf(" Create two threads which immediately attempt to lock and unlock the mutex, print something and exit by returning. main prints something, unlocks the mutex and joins the threads.  main should continue before the threads exit.\n");
	gtthread_t th1,th2;

	gtthread_init(1000);

	gtthread_mutex_init(&g_mutex);
        gtthread_mutex_lock(&g_mutex);
	gtthread_create(&th1, worker, NULL);
	gtthread_create(&th2,worker,NULL);
	printf("Main is printing something\n");
	gtthread_mutex_unlock(&g_mutex);

	gtthread_join(th1, NULL);
	gtthread_join(th2,NULL);
	return 0;
}
