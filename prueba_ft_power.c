#include <stdio.h>

int		ft_power(int base, int exp)
{
	int	i;
	int	result;

	result = 1;
	i = 0;
	while (++i <= exp)
		result = result * base;
	return (result);
}

int main()
{
	int a, b;
	a = 2;
	b = 0;

	printf("%d^%d = %d",a, b, ft_power(a, b));
	return (0);
}