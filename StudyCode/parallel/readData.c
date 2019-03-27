#include <stdio.h>
#include <stdlib.h>

void handle_error(const char* str, int exitNum);

int main()
{
  FILE *pf = fopen("test.txt", "r");
  if(pf == NULL)
      handle_error("fopen", -1);

  int sum = 0;
  if( EOF == fscanf(pf, "%d", &sum) )
      handle_error("fscanf", -1);
  
  int* arr = (int *)malloc(sum * sizeof(int));
  int* index = arr;
  while( EOF != fscanf(pf, "%d", index) && (index - arr +1) <= sum) 
       ++index;
  int i = 0;
  index = arr;
  while(i++ < sum){
  //    printf("index[%d] = %d\n", i - 1, *index);
      ++index;
  }
  
  printf("the num sum is %d\n", index - arr );

  fclose(pf);
  return 0;
}


void handle_error(const char* str, int exitNum)
{
  perror(str);
  exit(exitNum);
}
