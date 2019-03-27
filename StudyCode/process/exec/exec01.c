#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
  if(argc < 2){
      printf("argc < 2\n");
      return 0;
  }
  execvp("/bin/ls",argv);
  return 0;
}
