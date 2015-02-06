/*
  Test 7
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
  Distributed under terms of the MIT license.  
*/

#include <stdio.h>
#include <gtthread.h>

void* worker(void* arg)
{
	gtthread_t th;
	int i;
	if(arg != NULL)
		gtthread_create(&th, worker, NULL);
	for(i=0; i < 10; ++i ){
		printf("Hi: %lu\n",gtthread_self());
		gtthread_yield();
	}
	return NULL;
}

int main()
{
    printf(" Each copy loops 10 times, printing 'Hi: X' and busy waiting. The statements should interleave in some rough fashion.\n");
	gtthread_t th;

	gtthread_init(1000);
	gtthread_create(&th, worker, (void*) 1);
	gtthread_join(th, NULL);
	return 0;
}
