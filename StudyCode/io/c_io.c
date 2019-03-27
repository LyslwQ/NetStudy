#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 1024*1024

void handle_err(const char* str, int exitno);

int main()
{
  FILE *in   = fopen("testIN.txt", "rb");
  if(in == NULL)
      handle_err("open file", 1);
  FILE *out  = fopen("c_testOUT.txt", "a");
  if(out == NULL)
      handle_err("open file", 1);

  /*char ch = fgetc(in);
  while(ch != EOF){
      putchar(ch);
      fputc(ch, out);
      ch = fgetc(in);
  }
*/
  char buff[BUFFSIZE];
  memset(buff, '\0', sizeof(buff)/sizeof(char));
  while( fread(buff, sizeof(buff), 1, in) == 1){
      fwrite(buff, sizeof(buff), 1, out);
  }
  if(ferror(in))
      handle_err("read error", 1);
  fclose(in);
  fclose(out);
  puts("over");
  return 0;
}


void handle_err(const char* str, int exitno)
{
  perror(str);
  exit(exitno);
}
