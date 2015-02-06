/*
  Test 1b 
  Enrique Saurez :) 
  esaurez@gatech.edu
  Copyright (C) 2015 
  Distributed under terms of the MIT license.  
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
    printf(arg);
    return NULL;
}

int main()
{
	char* arg = "Hello World\n";
	gtthread_t th1, th2;

	srand(time(NULL));

	gtthread_init(1000);

	gtthread_create(&th1, producer, (void *) arg);


	while(1);

	return 0;
}
