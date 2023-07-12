// **********************************************************
// OJO!!!!! HAY QUE SUSTITUIR TODOS LOS PRIINTF POR FT_PRINTF
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	lens1;
	size_t	lens2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	newstr = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		newstr[i] = s1[i];
		i ++;
	}
	while (i < lens1 + lens2)
	{
		newstr[i] = s2[i - lens1];
		i ++;
	}
	newstr[i] = '\0';
	return (newstr);
}

size_t	ft_len_capture(int signal, size_t bits, size_t len_capture, char *str)
{
	if (bits < __CHAR_BIT__ * sizeof(size_t))
	{
		if (signal = SIGUSR2)
			len_capture += ft_power(2, bit_counter);
	}
	if (bits == __CHAR_BIT__ * sizeof(size_t))
	{
		str = malloc(len_capture +1);
		if (!str)
			return (0);
		return (1);
	}

	return (0);
}

void	signal_handler(int signal)
{
	static size_t	i;
	static size_t	len_capture;
	static size_t	bit_counter;
	static char		*str;

	if (!len_capture)
		len_capture = ft_len_capture(signal, bit_counter, len_capture);

	if (i < sizeof(char) * __CHAR_BIT__)
	{
		if (signal == SIGUSR1)
		{
			printf("señal recibida = 0\n");
			i++;
		}
		if (signal == SIGUSR2)
		{
			printf("señal recibida = 1\n");
			letter += ft_power(2, i);
			i++;
		}
	}
	printf("La letra recibida es %c\n", letter);
	usleep(100);
}

int	main(void)
{
	static size_t	i;
	static size_t	len;
	pid_t			server_pid;
	char			*txt;

	server_pid = getpid();
	printf("El PID del programa servidor es: %d\n", server_pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		usleep(1);
	return (0);
}