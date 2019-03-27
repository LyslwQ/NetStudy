#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

void exit_statu(int statu, pid_t pid)
{
  printf("a child exit,pid = %d\n", pid);
  if(WIFEXITED(statu) == true )
      printf("exit statu = %d\n", WEXITSTATUS(statu));
  if(WIFSIGNALED(statu) == true)
      printf("term by the signal = %d\n", WTERMSIG(statu));
}

int main(void)
{
  const int NUM = 3;
  int num = 0;
  pid_t pid;
  while( num++ < NUM){
      pid = fork();
      if(pid == 0)
          break;
  }

  if(pid > 0){
      int ret = 0, statu;
      num = 0;
      while(1){
          sleep(1);
          printf("parent waiting for child...\n");
          ret = waitpid(0, &statu, WNOHANG);
          if(ret > 0){
              exit_statu(statu, ret);
              if(++num == NUM)
                 break;
          }
      }
      printf("The parent exit\n");
  }
  if(pid == 0){
      printf("I am child, pid = %d\n", getpid());
      sleep(10);
      return num;
  }
  
      return 0;
}
