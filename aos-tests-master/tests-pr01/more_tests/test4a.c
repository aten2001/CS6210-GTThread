/*
  Test 4a
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/

#include <stdio.h>
#include <gtthread.h>

  gtthread_t th;
  int function(gtthread_t th2){
    if(gtthread_equal(th,th2)){
      printf("They are equal\n");
    }
    else{
      printf("Should not print this\n");
    }
    return 0;
  }

void* worker2(void* arg)
{
  int i;
  for(i =0;i<99999999;++i);
  return NULL;
}

int main()
{
  printf("Should say that the global descriptor and the function parameter descriptor are equal.\n");
  gtthread_init(1000);
  gtthread_create(&th, worker2,NULL);
  function(th);
  return 0;
}