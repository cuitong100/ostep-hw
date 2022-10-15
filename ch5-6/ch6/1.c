#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

long nanosec(struct timeval t){
  return((t.tv_sec * 1000000 + t.tv_usec) * 1000);
}

int main(){
  int i;
  long N = 1000000; // iterate 1 million times
  float avgTimeSysCall;
  struct timeval t1, t2;

  gettimeofday(&t1, NULL);
  for (i = 0; i < N; i++) {
    getpid();
  }
  gettimeofday(&t2, NULL);
  avgTimeSysCall = (nanosec(t2) - nanosec(t1)) / (N * 1.0);

  printf("Average time for System call getpid : %f\n", avgTimeSysCall);
  return 0;
}