#include <signal.h>
#include <iostream>
#include <unistd.h>


// �źŴ���ص�����
void signal_handler(int signum, siginfo_t *info, void *ptr)
{
	printf("signum = %d\n", signum); // �źű��
	printf("info->si_pid = %d\n", info->si_pid); // �Է��Ľ��̺�
	printf("info->si_sigval = %d\n", info->si_value.sival_int); // �Է����ݹ�������Ϣ
}

int main()
{
	struct sigaction act, oact;

	act.sa_sigaction = signal_handler; //ָ���źŴ���ص�����
	sigemptyset(&act.sa_mask); // ������Ϊ��
	act.sa_flags = SA_SIGINFO; // ָ������ signal_handler

	// ע���ź� SIGINT
	sigaction(SIGINT, &act, &oact);

	while (1)
	{
		printf("pid is %d\n", getpid()); // ���̺�

		pause(); // �����źţ��˺���������
	}

	return 0;
}