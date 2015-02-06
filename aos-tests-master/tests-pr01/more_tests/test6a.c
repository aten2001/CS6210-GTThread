/*
  Test 6a
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
  Distributed under terms of the MIT license.  
*/

#include "gtthread.h"
#include <stdio.h>

gtthread_t child1,child2;
gtthread_t parent;

void* worker(void* arg)
{
  int i = 0;
  for (i = 0; i < 20; ++i) {
    printf("Child running %lu\n",gtthread_self());
    gtthread_yield();
  }
  return NULL;
}

int main()
{
  printf("Tests thread interleaving with yield.\n");
  gtthread_init(1000);
  gtthread_create(&child1, worker, NULL);
  gtthread_create(&child2,worker,NULL);
  gtthread_join(child1,NULL);
  gtthread_join(child2,NULL);
  return 0;
}
