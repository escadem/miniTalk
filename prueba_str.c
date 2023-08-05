#include <stdio.h>

void modificar_str(char *str, char c)
{
	int pos = 0;

	str[pos] = c;
}

int main(void)
{
	char	str[]= "Prueba";

	modificar_str(str, 'a');
	printf("%s\n", str);
	return (0);
}