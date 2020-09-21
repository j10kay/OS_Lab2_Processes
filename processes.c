#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>

#define   MAX_COUNT  200

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
     pid_t  child1_pid, child2_pid;
	
     child1_pid = fork();
  
     if (child1_pid < 0) {
         printf("Error, first child process not created.\n");
     } else if (child1_pid == 0) {
         ChildProcess();
         exit(0);
       
     } else {
         ParentProcess();
         child2_pid = fork();
         if (child2_pid < 0) {
           printf("Error, second child process not created.\n");
         } else if (child2_pid == 0) {
            ChildProcess();
            exit(0);
         } else {
            ParentProcess();
         }
    }
  
  return;
}

void  ChildProcess(void)
{
     int i, number_of_iterations;
     time_t t;

     srand((unsigned) time(&t));
     number_of_iterations = rand() % 30;

     printf("New child spawned. Randomize sleep for %d iterations.\n", number_of_iterations);
     for (i = 0; i < number_of_iterations; i++) {
       printf("Child Pid: %d is going to sleep!\n", getpid());
       unsigned sleep_time = rand() % 10;
       sleep(sleep_time);
       printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
     }
}

void  ParentProcess(void)
{
  int status;
  pid_t completed_pid = wait(&status);
  printf("Child Pid: %d has completed\n", completed_pid);
}