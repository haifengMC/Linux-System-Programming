#include <signal.h>
#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		pid_t pid, pid_self;
		union sigval tmp;

		pid = atoi(argv[1]); // ���̺�
		if (argc >= 3)
		{
			tmp.sival_int = atoi(argv[2]);
		}
		else
		{
			tmp.sival_int = 100;
		}

		// ������ pid������ SIGINT �źţ����� tmp ���ݹ�ȥ
		sigqueue(pid, SIGINT, tmp);

		pid_self = getpid(); // ���̺�
		printf("pid = %d, pid_self = %d\n", pid, pid_self);
	
}

	return 0;
}