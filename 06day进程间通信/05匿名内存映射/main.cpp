#include <iostream>
#include <unistd.h>
#include <sys/mman.h>

using namespace std;

int main()
{
	int* i = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

	pid_t pid = fork();

	switch (pid)
	{
	case -1:
		munmap(i, sizeof(int));
		return -1;
	case 0:
		while (true)
		{
			cout << "child: " << ++*i << endl;
			sleep(1);
		}
		break;
	default:
		while (true)
		{
			cout << "father: " << --*i << endl;
			sleep(1);
		}
		break;
	}

	return 0;
}