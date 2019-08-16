#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
	mkfifo("fifo1_2", 0666);

	int fdread = open("fifo1_2", O_RDONLY);
	int fdwrite = open("fifo2_1", O_WRONLY);

	if (-1 == fdread || -1 == fdwrite)
	{
		perror("open err");
		return 1;
	}
	cout << "open 1 ok" << endl;

	pid_t pid = fork();

	switch (pid)
	{
	case -1:
		perror("fork err");
		break;
	case 0:
		while (true)
		{
			char buf[64] = { 0 };
			int n = read(fdread, buf, sizeof(buf) - 1);
			cout << buf << endl;
		}
		break;
	default:
		while (true)
		{
			char buf[64] = { 0 };
			int n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
			cout << n << endl;
			sleep(5);
			if (0 == n) return 0;
			buf[n -1] = 0;
			write(fdwrite, buf, n);
		}
		break;
	}

	return 0;
}