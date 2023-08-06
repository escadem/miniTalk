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

static int	ft_len_capture(int signal, size_t *bits, size_t *len, char **str)
{
	if (signal == SIGUSR2)
		*len += ft_power(2, *bits);
	if (++(*bits) == __CHAR_BIT__ * sizeof(size_t))
	{
		*str = calloc(((*len) + 1), sizeof(char));
		if (!*str)
			return (0);
		return (1);
	}
	return (0);
}

void	ft_receive_str(int signal, char **str, size_t *bits)
{
	static size_t	pos;
	static char		letter;
	static size_t	counter;

	printf("bits = %zu, counter = %zu\n", *bits, counter);
	if (counter == __CHAR_BIT__ * sizeof(char))
	{
		printf("letter = %d, letter = %c\n", letter, letter);
		printf("pos = %zu\n", pos);
		// printf("str[%zu]= %c\n", pos, str[pos]);
		// str[pos] = 'a';
		*str[pos] = letter;
		pos++;
		letter = 0;
		counter = 0;
	}
	if (signal == SIGUSR2)
	{
		letter += ft_power(2, counter);
		printf("\tvalor de letter = %d\n", letter);
	}
	counter++;
	(*bits)++;
}

void	signal_handler(int signal)
{
	static size_t	len_capture;
	static size_t	bits;
	static char		*str;

	if (bits < __CHAR_BIT__ * sizeof(size_t))
	{
		ft_len_capture(signal, &bits, &len_capture, &str);
	}
	else if (bits < sizeof(char) * __CHAR_BIT__ * len_capture + __CHAR_BIT__ * sizeof(size_t))
	{
		printf ("len a recibir = %zu\n", len_capture);
		ft_receive_str(signal, &str, &bits);
	}
	usleep(100);
}

int	main(void)
{
	pid_t			server_pid;

	server_pid = getpid();
	printf("El PID del programa servidor es: %d\n", server_pid);
	signal(SIGUSR1, &signal_handler);
	signal(SIGUSR2, &signal_handler);
	while (1)
		usleep(1);
	return (0);
}
