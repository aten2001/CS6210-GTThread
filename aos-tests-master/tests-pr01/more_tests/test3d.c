/*
  Test 3d 
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/

#include <stdio.h>
#include <gtthread.h>

  gtthread_t th1,th2;

void* worker2(void* arg)
{
  int i;
  for(i =0;i<99999999;++i);
  printf("thr1 existing...\n");
  return NULL;
}

void* worker(void* arg)
{
  gtthread_join(th2, NULL);
  printf("thr2 exiting...\n");
  return NULL;
}

int main()
{
  printf("Tests an explicitly created thread joining another.  Thread 1 should print its message before thread 2.\n");


  gtthread_init(1000);
  gtthread_create(&th1, worker, NULL);
  gtthread_create(&th2, worker2,NULL);
  while(1);
  return 0;
}