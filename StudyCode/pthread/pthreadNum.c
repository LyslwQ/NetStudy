#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void* pthread_func(void* argv);

int main(void)
{
  pthread_t  tid;
  int i = 0, ret;
  while(1){
      ret = pthread_create(&tid, NULL, pthread_func, NULL);
      if(ret != 0){
          printf("pthread_create error:%s\n", strerror(ret));
          exit(1);
      } 
      printf("sum of threadNUM:%d\n", ++i);
  }
  return 0;
}

void* pthread_func(void* argv)
{
  while(1)
      sleep(1);
}
