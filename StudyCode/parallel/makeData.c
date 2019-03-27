#include <stdio.h>
#include <stdlib.h>


void handle_error(const char* str, int exitNum);
int main(int argc, char* argv[])
{
  if(argc < 2)
      handle_error("Usage: sumNum", 1);

  int sum = atoi(argv[1]);
  FILE *pf = fopen("test.txt", "w+");
  if( pf == NULL)
      handle_error("fopen", -1);
  
  fprintf(pf, "%d ", sum);
  int i = 0;
  for(; i < sum; ++i)
      fprintf(pf, "%f ", 2.0);  
  fclose(pf);
  printf("written %d num\n", i);
  return 0;
}


void handle_error(const char* str, int exitNum)
{
  perror(str);
  exit(exitNum);
}
