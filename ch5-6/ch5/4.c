#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int flag = 0;
const int MAX = 1;
int main()
{
	char * path = "/bin/ls";
	char * arg1 = "ls";
	char * arg2 = "/";
	char * argv[] = { arg1, arg2, NULL };
	for(flag = 0;flag < MAX; ++flag) {
		int rc = fork();
		if (rc < 0) {
			fprintf(stderr, "fork failed");
			exit(1);
		} else if (rc == 0) {
			switch(flag) {
			case 0:
				execl(path, arg1, arg2, NULL);
				break;
			case 1:
				execle(path, arg1, arg2, NULL);
				break;
			case 2:
				execlp(path, path, arg2, NULL);
				break;
			case 3:
				execv(path, argv);
				break;
			case 4:
				execvp(arg1, argv);
				break;
			case 5:
				execvpe(arg1, argv);
				break;
			default: break;
			}
		} else {
			wait(NULL);
		}
	}
	return 0;
}