#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

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

  int fd = open(argv[1], O_RDONLY);
  if(fd < 0)
      handle_err("open", 2);

  int file_len = lseek(fd, 0, SEEK_END);
  if(file_len == -1)
      handle_err("lseek", 3); 

  char* p_mmap = mmap(NULL, file_len, PROT_READ, MAP_SHARED, fd, 0);
  if(p_mmap == MAP_FAILED)
      handle_err("mmap", 4);
  close(fd);
  unlink(argv[1]);  //使该文件为临时文件，
                   //当此次进程结束后，该文件会被自动删除。（避免开太多文件）
  while(1){
     printf("%s\n", p_mmap);
     sleep(1);
  }
  munmap(p_mmap, file_len);
  return 0;
}
