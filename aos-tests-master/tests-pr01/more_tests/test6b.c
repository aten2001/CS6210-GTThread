/*
  Test 6b
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
  Distributed under terms of the MIT license.  
*/

#include <stdio.h>
#include <gtthread.h>

#define NUM_THREADS 100

gtthread_mutex_t g_mutex;
int g_num = 0;

void* worker(void* arg)
{
	int i,j=0;
	while(j < 5){
		gtthread_mutex_lock(&g_mutex);
		printf("Mutex Lock obtained by: %lu\n", gtthread_self());
		gtthread_mutex_unlock(&g_mutex);
		gtthread_yield();
		++j;
	}	
    return NULL;
}

int main()
{
	printf("Each threads should write five times, interleaved\n");
	long i;
	gtthread_t th1,th2;

	gtthread_init(1000);
	gtthread_mutex_init(&g_mutex);
	gtthread_mutex_lock(&g_mutex);
	gtthread_create(&th1, worker, NULL);
	gtthread_create(&th2,worker,NULL);	
	printf("Hello is main!\n");
	gtthread_mutex_unlock(&g_mutex);
	gtthread_join(th1, NULL);
	gtthread_join(th2,NULL);
	return 0;
}
