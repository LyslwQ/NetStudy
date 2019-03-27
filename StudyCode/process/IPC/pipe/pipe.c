#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <memory.h>


int main(void)
{
  const int MAX_BUFFSIZE = 100;
  int pipe_fd[2];
  if(pipe(pipe_fd) == -1){
      perror("pipe error");
      exit(1);
  }
  
  int fork_ret = fork();
  if( fork_ret > 0){
      close(pipe_fd[0]); //关闭读端
      char buff[] = "hello girl *_*\n";
      write(pipe_fd[1], buff, sizeof(buff)/sizeof(char));
      wait(NULL);       //回收子进程
  }
  else if(fork_ret == 0){
      close(pipe_fd[1]); //关闭写端
      char buff[MAX_BUFFSIZE];
      memset(buff, '\0', sizeof(buff));
      int n = read(pipe_fd[0], buff, sizeof(buff)/sizeof(char));
      if(n == -1){
          perror("read error");
          exit(1);
      }
      write(STDOUT_FILENO, buff, n);
  }
  return 0;
}
