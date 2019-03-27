#include <stdio.h>

void loseSpace(char str[]);

int main()
{
  char str[50] = "hey girl what  hello     boy";
  loseSpace(str);
  printf("%s\n", str);
  return 0;
}

void loseSpace(char str[])
{
  int read =0, write = 0;
  for(; str[read] != '\0'; ++read){
      if(str[read] == ' ')
          continue;
      if(read != write)
          str[write] = str[read];
      ++write;
  }
  str[write] = '\0';
}
