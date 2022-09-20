// Write a programthat calls fork(). Before calling fork(), have the
// main process access a variable (e.g., x) and set its value to something
// (e.g., 100). What value is the variable in the child process?
// What happens to the variablewhen both the child and parent change
// the value of x?



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int x = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        printf("fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("I am child process (pid:%d), x = %d\n", (int) getpid(), x);
        x = 10;
        printf("I am child process (pid:%d), x = %d\n", (int) getpid(), x);
    } else {
        // parent process
        printf("I am parent process (pid:%d), x = %d\n", (int) getpid(), x);
        x = 20; 
        printf("I am parent process (pid:%d), x = %d\n", (int) getpid(), x);
       
    }
    return 0;
}




// Answer: When we haven't change the value of x, x in the child process would be 100.
// After we change it in both child and parent, x would be the certain value we changed in child and parent.
// In our case, x = 20 in the parent process, and x = 10 in the child process.
 

