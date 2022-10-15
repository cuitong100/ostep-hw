// Write a program that opens a file (with the open() system call)
// and then calls fork() to create a new process. Can both the child
// and parent access the file descriptor returned by open()? What
// happens when they are writing to the file concurrently, i.e., at the
// same time?


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd = open("./test", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        printf("fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        char *words = "child is writing\n";
        int error = write(fd, words, sizeof(char) * strlen(words));
        printf("child has : %d error\n", error == -1? 1 : 0);
    } else {
        // parent process
        char *words = "parent is writing\n";
        int error = write(fd, words, sizeof(char) * strlen(words));
        printf("parent has %d error\n", error == -1? 1 : 0);
        wait(NULL);
        close(fd);
    }
    return 0;
}

// Answer: The child and parent can access the file descriptor returned by open(). However, their schedual is not fixed. 