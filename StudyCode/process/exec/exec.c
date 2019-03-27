#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  printf("exec: Hello\n");
  pid_t p = fork();
  if(p == 0){
      if( -1 == execl("./exec-test.out", "exec-test", NULL)){
          printf("execl error\n");
          exit(1);
      }
  }
  else if(p > 0)
      printf("exec: world\n");
  return 0;
}
