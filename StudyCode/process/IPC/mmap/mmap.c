#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
  int fd = open("text.txt", O_RDWR);
  if(fd < 0){
      perror("open file error");
      exit(1);
  }
  int len = lseek(fd, 0, SEEK_END);
  char *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(p == MAP_FAILED){
      perror("mmap error");
      exit(1);
  }
  close(fd);
  p[0] = 'A';
  munmap(p, len);
  return 0;
}
