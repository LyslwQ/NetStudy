#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void printSigs(sigset_t *sigs);

int main(void)
{
  sigset_t sigs;
  sigemptyset(&sigs);
  sigaddset(&sigs, SIGINT);
  sigprocmask(SIG_BLOCK, &sigs, NULL);
  while(1){
      sigpending(&sigs);
      printSigs(&sigs);
      sleep(1);
  }
  return 0;
}


void printSigs(sigset_t *sigs)
{
  if(sigs == NULL)
      return;
  int i = -1;
  while(++i < 32){
      if(1 == sigismember(sigs, i)) 
          putchar('1');
      else
          putchar('0');
  }
  puts("");
}
