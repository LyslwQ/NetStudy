#include	"unp.h"

//该SIGCHLD处理函数是不可靠的.
//当信号被阻塞期间，即使产生多次信号，该信号也只被传递一次。
//当在信号处理函数执行期间，有另外多个进程终止，
//则会导致有进程未被回收处理。
void
sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}
