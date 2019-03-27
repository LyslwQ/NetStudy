#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

const int FILE_SIZE = 1024 * 4;

void handle_err(const char* str, int exitno)
{
  perror(str);
  exit(exitno);
}


int main(int argc, char* argv[])
{
  if(argc < 2){
      printf("Usage: file\n");
      exit(1);
  }

  int fd = open(argv[1], O_RDWR|O_CREAT, 0777);
  if( fd < 0 )
      handle_err("open file error!\n", 1);
  
  if( lseek(fd, FILE_SIZE - 1, SEEK_SET) < 0) //扩展文件大小，为0的文件无法作为传输介质
      handle_err("lseek error\n", 2);
  if( -1 == write(fd, "\0", 1))  //是"\0"而不是‘\0’
      handle_err("write error\n", 3);
  char* map_fd = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(map_fd == MAP_FAILED)
      handle_err("mmap error\n", 3);
  close(fd);
  int i = 0;
  while(1){
      sprintf(map_fd, "Hey girl*_*lrig%d", ++i);
      sleep(1);
  }
  munmap(map_fd, FILE_SIZE);
  printf("process over...");
  return 0;
}
