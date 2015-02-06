/*
  Test 4d
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/


#include <stdio.h>
#include <gtthread.h>

gtthread_t th1, th2;
void* worker1(void* arg)
{
  if(gtthread_equal(th2,gtthread_self())){
    printf("Should not print this\n" );
  }
  else{
    printf("They are not equal\n");
  }
  return NULL;
}

void* worker2(void* arg)
{
  int i;
  for(i = 0; i < 99999999; ++i);
  return NULL;
}


int main()
{
  printf(" Tests gtthread_self and gtthread_equal. Should say that they are not equal\n");


  gtthread_init(1000);

  gtthread_create(&th1, worker1, (void*)1);
  gtthread_create(&th2, worker2, (void*)1);

  gtthread_join(th1, NULL);
  gtthread_join(th2, NULL);
  return 0;
}
