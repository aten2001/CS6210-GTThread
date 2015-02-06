#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

/* Tests creation.
   Should print "Hello World!" */

void *thr1(void *in) {
    printf("Hello World Thr1!\n");
    fflush(stdout);
    return NULL;
}
void *thr2(void *in) {
    printf("Hello World Thr2!\n");
    fflush(stdout);
    return NULL;
}

int main() {
    gtthread_t t1;
    gtthread_t t2;
    gtthread_init(50000L);
    gtthread_create( &t1, thr1, NULL);
    gtthread_create( &t2, thr2, NULL);
    gtthread_join(t1,NULL);
    gtthread_join(t2,NULL);
    while(1);

    return EXIT_SUCCESS;
}
