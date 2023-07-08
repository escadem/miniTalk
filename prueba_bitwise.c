#include <stdio.h>

int	main()
{
	char			letra = '0';
	int				i = -1;
	int				valor[8];
	unsigned int	recalc_letra = 0;

	printf("la letra es %c\n", letra);
	printf("la letra %c en ASCII es %d\n\n", letra, letra);
	printf("Vamos a imprimir la letra %c en binario\n", letra);
	while(++i < 8)
		valor[7 - i] = (letra >> i) & 1;
	i = -1;
	printf("[");
	while (++i < 8)
		printf("%d ",valor[i]);
	printf("]\n");
	//
	//RECONVERTIR EL BINARIO EN LA LETRA
	//
	i = 9;
	while (--i > 0)
	{
		recalc_letra = 2 * recalc_letra + valor[8 - i];
		printf("\t\t%d, %d --> %u\n", i, valor[8 -i], recalc_letra);
	}
	printf("El valor de la letra es %d\n", recalc_letra);
	printf("La letra enviada es %c\n", recalc_letra);
	return 0;
}