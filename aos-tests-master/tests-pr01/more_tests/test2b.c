/*
  Test 2b 
  Enrique Saurez :)
  esaurez@gatech.edu
  Copyright (C) 2015  
*/
#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

void* thr1(void *in) {
  gtthread_exit("Success");
}

int main() {
    printf("Argument passing on join with return. Should print 'Success'.\n");
    gtthread_t t1;

    gtthread_init(50000L);
    gtthread_create( &t1, thr1, NULL);
    char* result;
    if(!gtthread_join(t1, (void**)&result)) {
      printf("%s\n",result);
    } else {
      printf("Failed.\n");
    }

    return EXIT_SUCCESS;
}
