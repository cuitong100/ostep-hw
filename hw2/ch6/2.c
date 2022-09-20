#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>

long nanosec(struct timeval t){
  return((t.tv_sec * 1000000 + t.tv_usec) * 1000);
}

int main() {

    // ensure both parent and child process run on the same cpu
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    int N = 1000000; // iterate 1 million times
    float avgTimeContextSwitch;
    struct timeval t1, t2;
    int first_pipefd[2], second_pipefd[2];
    
    if (pipe(first_pipefd) == -1) {
        exit(1);
    }
    if (pipe(second_pipefd) == -1) {
        exit(1);
    }

    pid_t cpid = fork();

    if (cpid == -1) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (cpid == 0) { // child process p1
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(1);
        }
        for (size_t i = 0; i < N; i++) {
            read(first_pipefd[0], NULL, 0); //then blocked
            write(second_pipefd[1], NULL, 0);
        }
    } else { // parent process p2
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(1);
        }
        gettimeofday(&t1, NULL);
        for (size_t i = 0; i < N; i++) {
            write(first_pipefd[1], NULL, 0); // then back to read
            read(second_pipefd[0], NULL, 0);
        }
        gettimeofday(&t2, NULL);
        
        avgTimeContextSwitch = (nanosec(t2) - nanosec(t1)) / (N * 1.0);
        printf("Average time for context switch : %f\n", avgTimeContextSwitch);
    }
    return 0;
}