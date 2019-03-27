#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
  char ch;
  while( (ch = getchar()) != EOF)
      putchar(toupper(ch));
  return 0;
}
