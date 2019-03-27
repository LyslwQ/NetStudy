#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
  int pid = fork();
  if(pid > 0){
      printf("I am parent,pid = %d\n I am die after 5s\n", getpid());
      sleep(5);
      exit(1);
  }
  else if(pid == 0){
      while(1){
          printf("I am child,pid = %d, ppid = %d\n", getpid(), getppid());
          sleep(1);
      }
  }
  return 0;
}
