#include <iostream>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_SIZE 128

using namespace std;

int main()
{
	int fd = open("mmap", O_RDWR | O_CREAT, 0666);
	truncate("mmap", FILE_SIZE);

	char* map = (char*)mmap(NULL, FILE_SIZE, 
		PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (MAP_FAILED == map)
	{
		perror("mmap err");
		return 1;
	}

	memset(map, 0, FILE_SIZE);

	pid_t pid = fork();
	switch (pid)
	{
	case -1:
		return 1;
	case 0:
		while (true)
		{
			char buf[64] = { 0 };
			int n = read(STDIN_FILENO, buf, sizeof(buf) - 1);
			

		}
		break;
	default:
		while (true)
		{

		}
		break;
	}


	return 0;
}