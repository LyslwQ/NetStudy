#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

struct msg_t
{
  int num;
  pthread_mutex_t       mutex;
  pthread_mutexattr_t   mutex_attr;
};

typedef struct msg_t msg_t;


int main(void)
{
  msg_t* mm;
  int fd = open("msg.txt", O_CREAT | O_RDWR, "0777");
  if( fd == -1){
      perror("open file");
      exit(1);
  }
  ftruncate(fd, sizeof(*mm));
  unlink("msg.txt");

  mm = mmap(NULL, sizeof(*mm), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(mm == MAP_FAILED){
      perror("mmap");
      exit(2);
  }
  close(fd); 
  memset(mm, 0, sizeof(*mm));

  pthread_mutexattr_init(&mm->mutex_attr);
  pthread_mutexattr_setpshared(&mm->mutex_attr, PTHREAD_PROCESS_SHARED);
  pthread_mutex_init(&mm->mutex, &mm->mutex_attr);

  int pid = fork();
  if(pid == 0){
      int i = 0;
      for(; i< 10; ++i){
          pthread_mutex_lock(&mm->mutex);
          printf("pid = %d, ++num = %d\n", getpid(), ++mm->num);
          pthread_mutex_unlock(&mm->mutex);
          sleep(1);
       }
  } 
  else if(pid > 0){
      int i = 0;
      for(; i< 10; ++i){
          pthread_mutex_lock(&mm->mutex);
          printf("pid = %d, ++num = %d\n", getpid(), ++mm->num);
          pthread_mutex_unlock(&mm->mutex);
          sleep(1);
       }
  } 
  else{
      perror("fork error");
      exit(1);
  } 

  pthread_mutexattr_destroy(&mm->mutex_attr);
  pthread_mutex_destroy(&mm->mutex);
  munmap(mm, sizeof(*mm));   
}
