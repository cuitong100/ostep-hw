#include<stdlib.h>
#include <stdio.h>  

int main()
{
	int * p = malloc(1 * sizeof(int));
	p = NULL;
	printf("value is : %d", *p);  
	free(p);
	return 0;
}