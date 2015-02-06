/*
  Test 2a 
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015
 * Distributed under terms of the MIT license.
    
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gtthread.h>

#define LOOP 100

gtthread_t g_th1, g_th2;
gtthread_mutex_t g_mutex;
int g_num = 0;

void* producer(void* arg)
{
    printf("thr1 exiting....\n");
    gtthread_exit(NULL);
    printf("Should not write this");
    return NULL;
}

int main()
{
	gtthread_t th1;

	srand(time(NULL));

	gtthread_init(1000);

	gtthread_mutex_init(&g_mutex);

	gtthread_create(&th1, producer, NULL);
	while(1);
	return 0;
}
