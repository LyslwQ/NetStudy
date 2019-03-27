#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define  MAX_PROCESS_NO  10

void handle_err(const char* str, int exit_no);
void ch_func();
void pa_func();
void handle_child_alrm(int sig);
void handle_parent_alrm(int sig);

pid_t pro_container[MAX_PROCESS_NO] = {0};

int main(void)
{
  pid_t ch_pid = -1;

  int i = MAX_PROCESS_NO;
  while(--i >= 0){
      ch_pid = fork();
      if(ch_pid == -1) 
          handle_err("fork", 1);
      if(ch_pid == 0)
          break;
      pro_container[i] = ch_pid;
  }
  if(ch_pid == 0)
      ch_func();
  if(ch_pid > 0){
      pa_func();
  }
 
  while(1); 
  return 0;
}


void pa_func()
{
  printf("I am parent(pid = %d), ready!\n", getpid());
  signal(SIGALRM, handle_parent_alrm);
  alarm(5);
}

void handle_parent_alrm(int sig)
{
  int i = -1;
  while(++i < MAX_PROCESS_NO){
      if( kill(pro_container[i], 0) != -1){ //进程存在
         printf("the child(pid = %d) is exit\n", pro_container[i]);
         kill(pro_container[i], SIGALRM);
         sleep(2);
      }     
  }
}


void ch_func()
{ 
  printf("I am child(pid = %d), ready!\n", getpid());
  signal(SIGALRM, handle_child_alrm);
  while(1);
}


void handle_child_alrm(int sig)
{
  printf("I am child(pid = %d), get the signal %d\n", getpid(), sig);
  exit(1);
}


void handle_err(const char* str, int exit_no)
{
    perror(str);
    exit(exit_no);
}
