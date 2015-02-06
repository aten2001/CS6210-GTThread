/*
  Test 3b
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/

#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

void* thr1(void *in) {
  int i;
  for(i=0;i<99999999;++i);
  printf("Thread 1 returning\n");
  return NULL;
}

int main() {
  printf(" Tests preemption and fair scheduling. \n");
  printf(" Like test3a except the busy wait lengths are swapped. Main should finish before the thread.\n");
  gtthread_t t1;
  int i;
  gtthread_init(1000L);
  gtthread_create( &t1, thr1, NULL);
  for(i=0;i<99999;++i);
  printf("Main finishing\n");
  gtthread_exit(NULL);
    return EXIT_SUCCESS;
}
