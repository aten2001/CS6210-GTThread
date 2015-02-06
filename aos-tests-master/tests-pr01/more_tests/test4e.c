/*
  Test 4e
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/


#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"
static char*result="success";
void* thr1(void *in) {
  gtthread_exit(result);
  printf("Should not print this\n");
  return NULL;
}

int main() {
    printf("Argument passing on join with return. Should print 'Success'.\n");
    gtthread_t t1;
    int i;
    gtthread_init(1000L);
    gtthread_create( &t1, thr1, NULL);
    char* result;
    for(i = 0; i<99999999;++i);
    if(!gtthread_join(t1, (void**)&result)) {
      printf("%s\n",result);
    } else {
      printf("Failed.\n");
    }

    return EXIT_SUCCESS;
}
