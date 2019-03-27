#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* pthread_fun01(void* argv);
void* pthread_fun02(void* argv);
void* pthread_fun03(void* argv);

int main(void)
{
  pthread_t pid01, pid02, pid03;
  void *exit_no01, *exit_no02, *exit_no03;
  int ret = pthread_create(&pid01, NULL, pthread_fun01, (void*)"hey girl"); 
  if(ret != 0){
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
        exit(1);
  }
  printf("main():a thread was created,pid = %x\n", pid01);


  pthread_create(&pid02, NULL, pthread_fun02, (void*)"hey gril");
  printf("main():a thread was created,pid = %x\n", pid02);

  pthread_create(&pid03, NULL, pthread_fun03, "hey girl");
  printf("main():a thread was created,pid = %x\n", pid03);
  pthread_cancel(pid03);

  pthread_join(pid01, &exit_no01);
  printf("the thread(pid = %x), exit_no = %d\n", pid01, (int)exit_no01);
  pthread_join(pid02, &exit_no02);
  printf("the thread(pid = %x), exit_no = %d\n", pid02, (int)exit_no02);
  pthread_join(pid03, &exit_no03);
  printf("the thread(pid = %x), exit_no = %d\n", pid03, (int)exit_no03);

  sleep(10);
  return 0;
}


void* pthread_fun01(void* argv)
{
  printf("pthread_fun01(): %s,the thread pid = %x\n", argv, pthread_self());
  sleep(1);
  return (void*)1;
}


void* pthread_fun02(void* argv)
{
  printf("pthread_fun02(): %s,the thread pid = %x\n", argv, pthread_self());
  sleep(1);
  pthread_exit((void*)2);
}


void* pthread_fun03(void* argv)
{
  printf("pthread_fun03(): %s,the thread pid = %x\n", argv, pthread_self());
  while(1){
      printf("pthread_func03():%s\n",  argv);
  }
}
