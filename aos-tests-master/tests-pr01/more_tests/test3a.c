/*
  Test 3a
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/

#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

void* thr1(void *in) {
  int i;
  for(i=0;i<99999;++i);
  printf("Thread 1 returning\n");
  return NULL;
}

int main() {
  printf(" Tests preemption and fair scheduling. \n");
  printf(" The thread busy waits, prints, and returns. Main does the same, but with a much longer busy wait. The thread should finish before main.\n");
  gtthread_t t1;
  int i;
  gtthread_init(1000L);
  gtthread_create( &t1, thr1, NULL);
  for(i=0;i<99999999;++i);
  printf("Main finishing\n");
  return EXIT_SUCCESS;
}
