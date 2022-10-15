#include<stdlib.h>
#include<stdio.h>
int main()
{
	int * p = (int *)malloc(100*sizeof(int));
	free(p);
	printf("%d\n", p[0]);
	return 0;
}