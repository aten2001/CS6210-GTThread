# aos-tests
Test cases for the AOS projects.
If you use this testcases I expect you to contribute by writing you own testscases and add them.
The testcase should just be a single c file (name it testX.c) and should terminate if successfull.
Also print a description of the expected behaviour of your testcase.
Prefered contribution methods are branching and pull request...
Hope this helps everybody.

# Usage
To run just copy the test folder into your folder with the gtthread.h and
gtthread.a (or adjust the paths in the Makefile).
Then run
``` make ```
in the tests folder to build all the testcases and if successfull this will run them
The script will prompt you through what to do and what the expected output
should be. If your version does not output the desired thing go fix it (or fix
the testcases  if you find errors there).
# Debugging
To create executables that can be debuged (e.g with gdb + ddd) you have to adapt
the makefile (explaination in the comments).
Then run:
``` make debug ```
This will generate executables with debug symbols included (you also have to
generate the object files of your library with debug flags enables).

# Further test cases to write
More tests for mutex locks, tests for round robin working correctly...

# Description of tests used for grading
test1a: 5 pts
   Tests thread creation.
   Create a thread that prints "Hello World!" and exits by returning. Main
   loops forever.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png) 
(test-12 - but no looping)

test1b: 3 pts
   Tests thread argument passing.
   Create a thread that prints the argument passed to it and exits by
   returning. Main loops forever.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png) 
test-13/16/17

test1c: 3 pts
   Tests thread join and return value.
   Create a thread that returns a string. Main joins the thread and prints the
   returned value.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-14 (but joining main from child) and test-18

test2a: 5 pts
   Tests thread termination with gthread_exit.
   Create a thread that prints "thr1 exiting..." and exits by calling
   gthread_exit(NULL). Main loops forever.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
(but no looping forever on main)

test2b: 3 pts
   Tests thread join and retrun value with gthread_exit.
   Create a thread that exits by calling gthread_exit with a string return
   value. Main joins the thread and prints the returned value.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)

test2c: 2 pts
   Tests main calling gthread_exit.
   Create a thread that loops forever. Main prints "main exiting..." and exits
   by calling gthread_exit(NULL).
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-26 and test-19 (not null)

test3a: 1 pts
   Tests preemption and fair scheduling.
   The thread busy waits, prints, and returns. Main does the same, but with a
   much longer busy wait. The thread should finish before main.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-27

test3b: 1 pts
   Tests preemption and fair scheduling.
   Like test3a except the busy wait lengths are swapped. Main should finish
   before the thread.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-28

test3c: 2 pts
   Tests interleaving between two spawned threads.  
   Main creates thr1 and thr2 which each loop five times: in the loop, each
   thread busy waits and then prints "thrX hello". Main loops forever. The two
   threads should alternate messages printed.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-29

test3d: 2 pts
   Tests an explicitly created thread joining another. 
   Create two threads.  Thread 1 busy waits for a long time and then exits,
   printing "thr1 exiting...". Thread 2 joins Thread 1 and prints "thr2
   exiting...". Main loops forever. Thread 1 should print its message before
   thread 2.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-30

test4a: 1 pts
   Tests gtthread_equal.
   Create a thread and store the descriptor in a global. Pass the thread's
   descriptor to a function. The gtthread_equal() function should say the
   global descriptor and the function parameter descriptor are equal.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-31

test4b: 1 pts
   Tests gtthread_equal.
   Create two threads. The gtthread_equal() function should say the second
   thread's descriptor is not equal to the first thread's descriptor.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-32

test4c: 1 pts
   Tests gtthread_self and gtthread_equal.
   Create a thread and store the descriptor in a global. The gtthread_equal()
   function should say the global descriptor and the descriptor returned by
   gtthread_self() are equal.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-33

test4d: 1 pts
   Tests gtthread_self and gtthread_equal.
   Create two threads. The gtthread_equal() function should say the second
   thread's descriptor is not equal to the descriptor returned by
   gtthread_self() in the first thread.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-34

test4e: 3 pts
   Tests a join long after a thread has terminated.
   Create a thread which immediately returns a static string. Busy wait in
   main, so that the thread has time to finish, and then join the thread and
   check the return value.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-35

test5a: 3 pts
   Tests mutexes.
   Initialize a mutex, lock the mutex.  Create two threads which immediately
   attempt to lock and unlock the mutex, print something and exit by returning.
   main prints something, unlocks the mutex and joins the threads.  main should
   continue before the threads exit.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-36

test5b: 1 pts
  Tests thread interleaving with mutexes.
  Initialize a mutex, lock the mutex.  Create two threads which immediately
  attempt to lock and unlock the mutex, then repeatedly busy wait, lock the
  mutex, print something, unlock, and exit by returning.  main prints
  something, unlocks the mutex and joins the threads.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-37

test5c: 1 pts
  Tests mutexes.
  Like test5a but with one thread.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-38

test6a: 2 pts
  Tests thread interleaving with yield.
  Create two threads, each of which yield then print a message.  main joins
  both threads and exits.  The messages should interleave.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-39

test6b: 1 pts
  Tests thread interleaving with yield and mutex locks.
  Like test5b except no busy waiting and yield after each lock, print, unlock
  sequence.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-40

test6c: 1 pts
  Tests yield with one schedulable thread.
  Like test6a but with one thread.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-41

test6d: 3 pts
  Tests mutexes.
  Initialize a mutex, lock the mutex.  Create a thread which immediately
  attempts to lock the mutex and print something.  main joins the thread
  without unlocking the mutex.  The program should either hang or exit after
  detecting deadlock (but neither thread should proceed).  
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-44

test7: 2 pts
  Tests an explicitly created thread creating another thread.
  Create a thread which immediately creates another instance of itself (with a
  NULL parameter so it doesn't continue creating new copies). Each copy loops
  10 times, printing "Hi: X" and busy waiting. The statements should interleave
  in some rough fashion.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-42

test8a: 1 pts
  Tests gtthread_cancel.
  Create a thread which prints "thr1 hi" forever.  main cancels the thread and
  calls gtthread_exit.  The program should stop.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-43

test8b: 1 pts
  Tests a different scheduling period.
  Same as test8a, except the thread is not canceled and the scheduling period
  is modified.
![Check](http://upload.wikimedia.org/wikipedia/commons/thumb/e/e9/Check_mark.svg/28px-Check_mark.svg.png)
test-45
  
