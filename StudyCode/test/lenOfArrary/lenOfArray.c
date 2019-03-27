#include <stdio.h>

int len(int arr[]);
int main()
{
  int intArr[10] = {1,1,1,1,1,1,1,1,1,1};
  //int arrLen = sizeof(intArr)/sizeof(int);
 /* int arrLen = len(intArr);
  printf("the len of array is %d\n", arrLen);
  */
  printf("%d\n", *(intArr+1));
  return 0;
}

int len(int arr[])
{
  return sizeof(arr)/sizeof(int);
}
