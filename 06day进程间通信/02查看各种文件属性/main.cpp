#include <iostream>
#include <unistd.h>

using namespace std;

#define pConf(fd, X)\
	cout << #fd" " << #X" " << fpathconf(fd, X) << endl 

int main()
{
	int pipefd[2];
	pipe(pipefd);
	pConf(pipefd[0], _PC_PIPE_BUF);
	pConf(pipefd[1], _PC_PIPE_BUF);
	pConf(pipefd[0], _PC_NAME_MAX);
	pConf(pipefd[1], _PC_NAME_MAX);

	return 0;
}