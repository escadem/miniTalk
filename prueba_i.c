#include <stdio.h>

int modi(int *i)
{
	return ((*i)++);
}

int main (void)
{
	int i = 0;

	while (i < 10)
		printf("i = %d\n", modi(&i));

	return (0);
}