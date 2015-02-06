/*
  Test 2c 
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/

#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

void* thr1(void *in) {
  while(1);
  return NULL;
}

int main() {
    printf("Should print 'main exiting...' and loop forever\n");
    gtthread_t t1;

    gtthread_init(50000L);
    gtthread_create( &t1, thr1, NULL);
    printf("main exiting ...\n");
    gtthread_exit(NULL);
    return EXIT_SUCCESS;
}
