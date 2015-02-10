Project		: GTThreads- A User Level Thread Library
Course 		: CS6210- Advanced Operating Systems
GT ID  		: 903049530
Submission Date : 6th Feb 2015

********************************************************************************************************************************************************************************************

Platform Used :
Ubuntu 12.04 64-bit x86 hardware (Virtualized)

********************************************************************************************************************************************************************************************

Premptive Scheduler Implementation :

	* Boolean value initialized is used to check whether gtthread_init(long period) has been called first or not
	* gtthread_init initializes the Scheduler with Signal Type SIGVTALRM.
	* On expiration of Virtual Timer(SIGVTALRM) is signaled to the running thread.
	* Three different queues are maintained : Ready Queue for threads ready to execute, Waiting queue for threads waiting on a thread to complete, Terminated Queue for threads terminated.
	* To execute a thread, the Scheduler dequeues a thread from the ready queue
		* If the Dequeued thread or the candidate is waiting on another thread, the thread being waited on is executed first.
		* If the Current thread is already terminated, the new Candidate is the new Current thread.
		* Else, the candidate thread is added to the Ready Queue, and context swapped.
	
		* If no candidate is available, and the current thread is not waiting on any other thread, Ready Queue is empty.

********************************************************************************************************************************************************************************************

How to Compile the Library: 

1. Extract the tarbell into a folder.
2. Run the make command to generate binaries gtthread.a and dining
3. Run './dining' to run the Dining Philospers code.

********************************************************************************************************************************************************************************************

How I prevent deadlocks in Dining Philosphers solution:

	* Chopsticks are initialized as mutex variables and Philosphers are initialized as various threads.
	* Philosphers are numbered 0-4 (5 Philosphers).
	* Picking up of Chopsticks happen in the following fashion:
		* If the Philospher is even numbered, the philospher picks the right chopstick first followed by left chopstick.
		* If the Philospher is odd numbered, the philospher picks the left chopstick first followed by right chopstick.
	* Releasing up of Chopsticks happen in the following fashion:
		* If the Philospher is even numbered, the philospher releases the left  chopstick first followed by right chopstick.
		* If the Philospher is odd numbered, the philospher releases the right chopstick first followed by left chopstick.
	* Implementing it this way ensures that there are no contention for the same chopstick and no Philospher is holding one chopstick and waiting on the other.

********************************************************************************************************************************************************************************************

Tarball details:
	C Files:
		* gtthread.c 	   - Main Thread Library implementing Functions.
		* gtthread_sched.c - Scheduler and Timing Functions.
		* gtthread_mutex.c - Synchronization Functions.
		* dining.c	   - Philospher Dining Implementation.
	
	Header Files
		* gtthread.h       	- Header File declaring core functions.
		* gtthread_sched.h 	- Header File declaring Scheduler functions.
		* gtthread_internals.h  - Data structures used in implmentation.
	MakeFile
		*makefile 		- Generates the Binary and can be executed using ./dining.

********************************************************************************************************************************************************************************************

Thoughts:
	
	* Websites used as References:
		* http://www.advancedlinuxprogramming.com/alp-folder/alp-ch04-threads.pdf
		* http://www-01.ibm.com/support/knowledgecenter/SSB27U_6.2.0/com.ibm.zvm.v620.edclv/ptcrea.htm%23wq3737
		* http://refspecs.linuxbase.org/LSB_3.1.1/LSB-Core-generic/LSB-Core-generic/libpthread-ddefs.html
		* http://www.scs.stanford.edu/histar/src/pkg/uclibc/libpthread/linuxthreads/descr.h
		* http://www.gnu.org/software/libc/manual/html_node/Setting-an-Alarm.html
		* https://sourceware.org/git/?p=glibc.git;a=tree;f=nptl;h=d0ce23d37e9b77d6ff82ffdee0f7a1f8f137aa41;hb=HEAD
		* http://nitish712.blogspot.in/2012/10/thread-library-using-context-switching.html

********************************************************************************************************************************************************************************************
