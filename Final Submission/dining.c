#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gtthread.h"
#define PHILOSPHER 5

gtthread_mutex_t chopsticks[PHILOSPHER];

void* philosopher(void* philIdPtr)
{
	int philId = *(int *)philIdPtr;
	int timer = 0;
	while(1)
	{
		printf("Philospher %d is thinking.\n", philId);
		timer = rand() % 10000 + 1;
		while(timer > 0)
			timer--;	
		if(philId % 2 == 0)
		{
			printf("Philosopher %d is trying to pick the right chopstick.\n", philId);
			gtthread_mutex_lock(&chopsticks[(philId+1) % PHILOSPHER]);
			printf("Philosopher %d is trying to pick the left chopstick.\n", philId);
			gtthread_mutex_lock(&chopsticks[philId]);
		}
		else
		{
			printf("Philosopher %d is trying to pick the left chopstick.\n", philId);
			gtthread_mutex_lock(&chopsticks[philId]);
			printf("Philosopher %d is trying to pick the right chopstick.\n", philId);
			gtthread_mutex_lock(&chopsticks[(philId+1) % PHILOSPHER]);
			
		}
		printf("Philosopher %d is eating.\n", philId);
		timer = rand() % 10000 + 1;
		while(timer > 0)
			timer--;		
		if(philId % 2 == 0)
		{
			printf("Philosopher %d is releasing the left chopstick.\n", philId);
			gtthread_mutex_unlock(&chopsticks[philId]);
			printf("Philosopher %d is releasing the right chopstick.\n", philId);
			gtthread_mutex_unlock(&chopsticks[(philId+1) % PHILOSPHER]);
		}
		else
		{
			printf("Philosopher %d is releasing the right chopstick.\n", philId);
			gtthread_mutex_unlock(&chopsticks[(philId+1) % PHILOSPHER]);
			printf("Philosopher %d is releasing the left chopstick.\n", philId);
			gtthread_mutex_unlock(&chopsticks[philId]);
		}
	}
	gtthread_exit(NULL);
	return NULL;		
}

int main()
{
	int i=0,pass;
	int philId[PHILOSPHER];
	gtthread_t philThread[PHILOSPHER];
	srand ( time(NULL) );
	gtthread_init(10);
	for(i=0; i<PHILOSPHER; i++)
	{
		pass=gtthread_mutex_init(&chopsticks[i]);
		if(pass==-1)
		{
			printf("Error: Mutex Initialization Phil");
		}
	}
	for(i=0; i<PHILOSPHER; i++)
	{
		philId[i] = i;
		gtthread_create(&philThread[i], philosopher,(void*)&philId[i]);
	}	
	for(i=0; i<PHILOSPHER; i++)
		gtthread_join(philThread[i], NULL);
	return 0;
}
		
