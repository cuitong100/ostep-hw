#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	int rc = fork();
	int wc = wait(NULL);
	if(rc < 0) {
		printf("fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("child pid %d wc %d \n", (int)getpid(), wc);
	} else {
		printf("parent pid %d wc %d \n", (int)getpid(), wc);
	}
	return 0;
}