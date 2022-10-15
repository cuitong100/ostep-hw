#include <stdio.h>
#include<stdlib.h>


int main(int argc, char * argv[])
{

	int* p = (int*) malloc(3 * sizeof(int));
	p[0] = 0;
	p[1] = 1;
	p[2] = 2;
	printf("p0: %d\n", p[0]);
	printf("p1: %d\n", p[1]);
	printf("p2: %d\n", p[2]);

	int* p1 = (int*) realloc(p, 4);
	
	p[3] = 3;
	printf("p0: %d\n", p[0]);
	printf("p1: %d\n", p[1]);
	printf("p2: %d\n", p[2]);
	printf("p3: %d\n", p[3]);
	// free(p);
	free(p1);

	return 0;
}