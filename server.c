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

void	ft_receive_str(int signal, char **str, size_t *bits, size_t *pos)
{
	// static size_t	pos;
	static char		letter;
	static size_t	counter;

	// printf("bits = %zu, counter = %zu\n", *bits, counter);
	if (signal == SIGUSR2)
	{
		letter += ft_power(2, counter);
		// printf("\tvalor de letter = %d\n", letter);
	}
	counter++;
	(*bits)++;
	if (counter == __CHAR_BIT__ * sizeof(char))
	{
		// printf("letter = %d, letter = %c\n", letter, letter);
		// printf("pos = %zu\n", *pos);
		(*str)[*pos] = letter;
		// printf("str[%zu] = %c\n", *pos, (*str)[*pos]);
		(*pos)++;
		letter = 0;
		counter = 0;
	}
	// printf("\t\t\t\tbits = %zu\n", *bits);
}

void	signal_handler(int signal)
{
	static size_t	len;
	static size_t	bits;
	static char		*str;
	static size_t	pos;

	if (bits < __CHAR_BIT__ * sizeof(size_t))
	{
		ft_len_capture(signal, &bits, &len, &str);
	}
	else if (bits < sizeof(char) * __CHAR_BIT__ * len + __CHAR_BIT__ * sizeof(size_t))
	{
		// printf ("len a recibir = %zu\n", len);
		ft_receive_str(signal, &str, &bits, &pos);
		// printf ("\t\tBITS == %zu\n", sizeof(char) * __CHAR_BIT__ * len + __CHAR_BIT__ * sizeof(size_t));
	}
	if (bits == sizeof(char) * __CHAR_BIT__ * len + __CHAR_BIT__ * sizeof(size_t))
	{
		// printf ("ENTRA BITS ==\n");
		len = 0;
		bits = 0;
		pos = 0;
		printf ("mensaje recibido... %s\n", str);
		free (str);
	}
	usleep(10);
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
