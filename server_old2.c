// **********************************************************
// OJO!!!!! HAY QUE SUSTITUIR TODOS LOS PRINTF POR FT_PRINTF
// 	O UTILIZAR LA FUNCIÓN write
// **********************************************************

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_power(int base, int exp)
{
	int	i;
	int	result;

	result = 1;
	i = 0;
	while (++i <= exp)
		result = result * base;
	return (result);
}

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i ++;
// 	return (i);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*newstr;
// 	size_t	lens1;
// 	size_t	lens2;
// 	size_t	i;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	lens1 = ft_strlen(s1);
// 	lens2 = ft_strlen(s2);
// 	newstr = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
// 	if (newstr == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < lens1)
// 	{
// 		newstr[i] = s1[i];
// 		i ++;
// 	}
// 	while (i < lens1 + lens2)
// 	{
// 		newstr[i] = s2[i - lens1];
// 		i ++;
// 	}
// 	newstr[i] = '\0';
// 	return (newstr);
// }

static int	ft_len_capture(int signal, size_t *bits, size_t *len, char **str)
{
	if (signal == SIGUSR2)
		*len += ft_power(2, *bits);
	if (++(*bits) == __CHAR_BIT__ * sizeof(size_t))
	{
		// printf("\tSE RESERVA LA MEMORIA PARA STR\n");
		// printf("\tANTES\n");
		// printf("\t\tdireccion de memoria del puntero str = %p\n", &str);
		// printf("\t\tdireccion de memoria donde apunta el puntero str = %p\n", str);
		*str = malloc(((*len) + 1) * sizeof(char));
		if (!*str)
			return (0);
		// if (*str)
		// {
		// 	printf("\tLA RESERVA DE MEMORIA SE HA ALOCADO CORRECTAMENTE\n");
		// 	printf("\tDESPUES\n");
		// 	printf("\t\tdireccion de memoria del puntero str = %p\n", &str);
		// 	printf("\t\tdireccion de memoria donde apunta el puntero str = %p\n", str);

		// }
		*str[*len] = '\0';
		return (1);
	}
	return (0);
}

void	ft_receive_str(int signal, char *str, size_t *bits)
{
	static size_t	pos;
	static char		letter;
	static size_t	counter;

	printf("entra en ft_recieve_str, bits = %zu\n", *bits);
	printf("counter = %zu\n", counter);
	printf("\tposicion de memoria en ft_receive_str: %p\n", &str);
	// if (*bits % __CHAR_BIT__ == 0)
	if (counter == __CHAR_BIT__ * sizeof(char))
	{
		printf("letter = %c\n", letter);
		printf("pos = %zu\n", pos);
		printf("str[%zu]= %c\n", pos, str[pos]);
		// str[pos] = 'a';
	// 	*str[pos] = letter;
		pos++;
		letter = 0;
		counter = 0;
	}
	if (signal == SIGUSR2)
	{
		printf("señal recibida = 1\n");
		letter += ft_power(2, counter);
		printf("\t\tvalor de letter = %d\n", letter);
	}
	counter++;
	(*bits)++;
}

// void	ft_receive_str(int signal, char *str, size_t bits)
// {
// 	static size_t	pos;
// 	static char		letter;

// 	if (bits < __CHAR_BIT__)
// 	{
// 		if (signal == SIGUSR2)
// 			letter += ft_power(2, bits);
// 		bits ++;
// 	}
// 	if (bits == __CHAR_BIT__)
// 	{
// 		str[pos] = letter;
// 		pos ++;
// 		bits = 0;
// 	}
// }


void	signal_handler(int signal)
{
	// static size_t	i;
	static size_t	len_capture;
	static size_t	bits;
	static char		*str;

	// printf("\t\tdireccion de memoria del puntero str = %p\n", &str);
	// printf("\t\tdireccion de memoria donde apunta el puntero str = %p\n", str);
	// printf("bits = %zu, len = %zu\n", bits, len_capture);
	if (bits < __CHAR_BIT__ * sizeof(size_t))
		ft_len_capture(signal, &bits, &len_capture, &str);
	// printf("\tbits = %zu, <%zu\n", bits, __CHAR_BIT__ * len_capture);
	else if (bits < sizeof(char) * __CHAR_BIT__ * len_capture + __CHAR_BIT__ * sizeof(size_t))
	{
	
		// printf("entra bucle letras\n");
		ft_receive_str(signal, str, &bits);
	}
	// else
	// {
	// 	printf("%s\n", str);
	// 	free(str);
	// 	bits = 0;
	// }
		
	// if (i < sizeof(char) * __CHAR_BIT__)
	// {
	// 	if (signal == SIGUSR1)
	// 	{
	// 		printf("señal recibida = 0\n");
	// 		i++;
	// 	}
	// 	if (signal == SIGUSR2)
	// 	{
	// 		printf("señal recibida = 1\n");
	// 		// letter += ft_power(2, i);
	// 		i++;
	// 	}
	// }
	// printf("La letra recibida es %c\n", letter);
	usleep(100);
}

int	main(void)
{
	// static size_t	i;
	// static size_t	len;
	// char			*txt;
	pid_t			server_pid;

	server_pid = getpid();
	printf("El PID del programa servidor es: %d\n", server_pid);
	signal(SIGUSR1, &signal_handler);
	signal(SIGUSR2, &signal_handler);
	while (1)
		usleep(1);
	return (0);
}
