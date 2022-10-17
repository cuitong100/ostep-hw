#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define PAGESIZE 4096
#define OFFSET 4096

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "error parameters!");
		exit(0);
	}
    int i, j;
	int numOfPages = atoi(argv[1]);  // the number of pages to touch
	int numOfTrials = atoi(argv[2]); // the number of trials
	
    // Initialize the entire array before starting the timer
	char* a = (char*)malloc(PAGESIZE * numOfPages * sizeof(char));
    for (i = 0; i < PAGESIZE * numOfPages; ++i) {
		a[i] = '0';
	}
	
    struct timespec start, end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	for (j = 0; j < numOfTrials; ++j) {
		for (i = 0; i < numOfPages * OFFSET; i += OFFSET) { // access one page each iteration 
			a[i] = '1';
		}
	}
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	
    printf("%f nano seconds\n",((end.tv_sec - start.tv_sec) * 1E9 + end.tv_nsec - start.tv_nsec) / (numOfTrials * numOfPages));
    free(a);
	return 0;
}