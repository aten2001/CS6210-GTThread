/*
  Test 3c
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/

#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

void* thr1(void *in) {
  int i;
  int counter = 0;
  while(counter < 5){
    for(i=0;i<99999999;++i);
    printf("Thread 1 returning\n"); 
    counter++;
  }
  return NULL;
}

void* thr2(void *in) {
  int i;
  int counter = 0;
  while(counter < 5){
    for(i=0;i<99999999;++i);
    printf("Thread 2 returning\n");
    counter++;
  }
  return NULL;
}

int main() {
  printf("   Tests interleaving between two spawned threads.  \n");
  printf(" Main creates thr1 and thr2 which each loop five times: in the loop, each thread busy waits and then prints 'thrX hello'. Main loops forever. The two threads should alternate messages printed.\n");
  gtthread_t t1,t2;

  gtthread_init(1000L);
  gtthread_create( &t1, thr1, NULL);
  gtthread_create( &t2, thr2, NULL);
  while(1);
  return EXIT_SUCCESS;
}
