/*
  Test 8a
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
  Distributed under terms of the MIT license.  
*/

#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

#define PTHREAD_CANCELED       ((void *)(size_t) -1)

gtthread_t main_thread;
void* thr1(void *in) {
  int i;
  while(1){
    printf("thr1  hi\n");
    for(i=0;i<999999;++i);///Busy wait
  }
  return NULL;
}

int main() {
    printf("  Create a thread which prints 'thr1 hi' forever. main cancels the thread and calls gtthread_exit.  The program should stop.\n");
    gtthread_t t1;
    int i;
    gtthread_init(50000L);
    gtthread_create( &t1, thr1, NULL);
    for(i=0;i<99999999;++i);///Busy wait
    gtthread_cancel(t1);
    gtthread_exit("Success");
    return EXIT_SUCCESS;
}
