// Write another program using fork(). The child process should
// print “hello”; the parent process should print “goodbye”. You should
// try to ensure that the child process always prints first; can you do
// this without calling wait() in the parent?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {   
    int rc = vfork();
	if (rc < 0) {
		printf("fork failed\n");
		exit(1);
	} else if (rc == 0) {
        // child process
		printf("hello\n");
        exit(0);
	} else {
        // parent process
		printf("goodbye\n");
	}
	return 0;
}

//Answer: vfork() can suspend the parent process until the child process finishes. This works perfectly on Linux, while it has some problem on mac.