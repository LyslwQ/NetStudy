#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{

  int num = 3, pid;
  while(num--){
      pid = fork();
      if(pid == 0)
          break;
  }

  if( pid == 0)
      printf("I am child,pid = %d\n", getpid());
  if( pid > 0){
      printf("I am parent,pid = %d\n", getpid());
      while(1){
          int pid_child;
          if((pid_child = wait(NULL)) == -1)
              break;
          else
              printf("I am parent,wait for the child pid = %d\n", pid_child);
      }
  }

  while(1)
      sleep(1);
  return 0;
}
