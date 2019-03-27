#include <fstream>
#include <cstdlib>
#include <iostream>

#define BUFFSIZE 1024 * 1024

using namespace std;

void handle_error(const char* str, int exitno);

int main()
{
  ifstream fileIS("testIN.txt");
  //ofstream fileOS("testOS.txt", ios::app);
  ofstream fileOS("testOS.txt");
   
  if(!fileIS.is_open())
      handle_error("open file", 1);
  if(!fileOS.is_open())
      handle_error("open file", 1);

  char buff[BUFFSIZE];
  while( !fileIS.eof()){
      fileIS.getline(buff, BUFFSIZE);
      fileOS<< buff<< endl;
  //    cout << buff<< endl;
  }
  fileOS.close();
  fileIS.close();
  cout << "over..."<< endl;
  return 0;
}


void handle_error(const char* str, int exitno)
{
  perror(str);
  exit(exitno);
}
