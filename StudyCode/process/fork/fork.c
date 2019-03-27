#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  int n = 0, m = 30;
  pid_t p = fork();
  if( p > 0){
          printf("I am parent,the child processId is:%d\n", p);
          printf("parent: n = %d", ++n);
  }
  else if( p == 0){
     printf("I am child, the processId is:%d\n", getpid());
     printf("child: n = %d", n);   
  }
  else
     exit(1);
  return 0;
}
