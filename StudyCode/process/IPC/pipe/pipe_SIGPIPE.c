#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
 * file: pipe_SIGPIPE.c
 * note: 验证当pipe读端关闭时，写端继续写数据
 *       则会产生SIGPIPE
 * */

int main(void)
{
  int pipe_fd[2];
  if(pipe(pipe_fd) == -1){
      perror("pipe error");
      exit(1);
  }
  int fork_ret = fork();
  if(fork_ret > 0){
      close(pipe_fd[0]);
      sleep(1);   //等待子进程关闭read端，造成SIGPIPE
      if( -1 == write(pipe_fd[1], "hello girl *_*\n", 20)){
          printf("write error\n");
          exit(1);
      }
      wait(NULL);
      while(1){
          printf("hello world\n");
          sleep(1);
      }
  }
  else if(fork_ret == 0){
      close(pipe_fd[1]);
      close(pipe_fd[0]);
  }
  else{
      perror("fork error");
      exit(1);
  }
  return 0;
}
