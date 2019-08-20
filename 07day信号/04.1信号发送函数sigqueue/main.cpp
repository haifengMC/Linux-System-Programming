#include <signal.h>
#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		pid_t pid, pid_self;
		union sigval tmp;

		pid = atoi(argv[1]); // 进程号
		if (argc >= 3)
		{
			tmp.sival_int = atoi(argv[2]);
		}
		else
		{
			tmp.sival_int = 100;
		}

		// 给进程 pid，发送 SIGINT 信号，并把 tmp 传递过去
		sigqueue(pid, SIGINT, tmp);

		pid_self = getpid(); // 进程号
		printf("pid = %d, pid_self = %d\n", pid, pid_self);
	
}

	return 0;
}