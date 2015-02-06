/*
  Test 6d
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
  Distributed under terms of the MIT license.  
*/

#include <stdio.h>
#include <gtthread.h>

#define NUM_THREADS 100

gtthread_mutex_t g_mutex;
int g_num = 0;

void* worker(void* arg)
{
  gtthread_mutex_lock(&g_mutex);
  printf("Mutex Lock obtained by: %lu\n", gtthread_self());
  gtthread_mutex_unlock(&g_mutex);
  return NULL;
}

int main()
{
  printf("The program should either hang or exit after detecting deadlock (but neither thread should proceed).\n");
  gtthread_t th1;
  gtthread_init(1000);
  gtthread_mutex_init(&g_mutex);
  gtthread_mutex_lock(&g_mutex);
  gtthread_create(&th1, worker, NULL);
  gtthread_join(th1, NULL);
  return 0;
}
