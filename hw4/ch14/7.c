#include<stdlib.h>
int main()
{
	int * p = (int *)malloc(100*sizeof(int));
	free(p+4);
	return 0;
}