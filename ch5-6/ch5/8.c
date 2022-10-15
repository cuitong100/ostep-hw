#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
	
    int pipefd[2];
	pipe(pipefd);

	int i = 0;
	int rc[2];

	char string[] = "Hello Pipe\n";
	char readbuffer[256];

	for(i = 0; i < 2; i++) {
		rc[i] = fork();
		if (rc[i] < 0) {
			printf("fork failed\n");
			exit(1);
		} else if (rc[i] == 0) {
			switch(i) {
				case 0:
					// child process 0
					// write to pipe
               		write(pipefd[1], string, strlen(string) + 1);
					exit(0);
				case 1:
					// child process 1
					// read from pipe
            		read(pipefd[0], readbuffer, sizeof(readbuffer));
                	printf("Received string: %s", readbuffer);
					exit(0);
			}
		}
	}
	waitpid(rc[0], NULL, 0);
	waitpid(rc[1], NULL, 0);
	return 0;
}