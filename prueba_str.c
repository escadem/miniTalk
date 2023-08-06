#include <stdio.h>
#include <stdlib.h>

void modificar_str(char **str, char c)
{
	int pos = 0;

	printf("Posicion de memoria str en funcion = %p\n", str);
	*str = malloc(100);
	*str[pos] = c;
	printf("Posicion de memoria str en funcion despues de malloc = %p\n", str);
}

int main(void)
{
	static char	*str;
	// char	str[]= "Prueba";

	printf("Posicion de memoria str en main = %p\n", str);
	printf("Posicion de memoria str en main = %p\n", &str);
	modificar_str(&str, 'a');
	printf("Posicion de memoria str en main despues de la funcion= %p\n", str);
	printf("%s\n", str);
	return (0);
}