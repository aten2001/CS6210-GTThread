/*
  Test 4c
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/


#include <stdio.h>
#include <gtthread.h>

gtthread_t th;
void* function(void* arg){
  if(gtthread_equal(th,gtthread_self())){
    printf("They are equal\n");
  }
  else{
    printf("Should not print this\n");
  }
}


int main()
{
  printf("Tests gtthread_self and gtthread_equal. Should return they are equal\n");
  gtthread_init(1000);
  gtthread_create(&th, function,NULL);
  gtthread_join(th,NULL);
  return 0;
}