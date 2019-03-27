#include <stdio.h>
#include <stdlib.h>

int main()
{
  int i = 0;
  int *p = NULL;
  do{
      p = (int*)malloc(i * 1024*1024);
      printf("the heap size = %dM\n ", i++);
  }while(p != NULL);
  return 0;
}
