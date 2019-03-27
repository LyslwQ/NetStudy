#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  if(argc != 2){
      fputs("Usage: wrapper file\n", stderr);
      exit(1);
  }
  int fd = open(argv[1], O_RDONLY);
  if(fd < 0){
      perror("open file error");
      exit(1);
  }

  dup2(fd, STDIN_FILENO);
  close(fd);
  execlp("./upper", "upper", NULL);
  perror("exec error\n");
  return 0;
}
