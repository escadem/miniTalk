// **********************************************************
// OJO!!!!! HAY QUE SUSTITUIR TODOS LOS PRINTF POR FT_PRINTF
// 	O UTILIZAR LA FUNCIÓN write
// **********************************************************

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	value;

	i = 0;
	sign = 1;
	value = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i ++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= (-1);
		i ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + ((int)(str[i] - 48));
		i ++;
	}
	return (sign * value);
}

void	ft_send_strlength(pid_t server_pid, char *str)
{
	size_t	i;
	size_t	signal;
	size_t	len;

	len = ft_strlen(str);
	i = -1;
	while (++i < sizeof(size_t) * __CHAR_BIT__)
	{
		signal = (len >> i) & 1;
		if (signal == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
	}
}

void	ft_send_str(pid_t server_pid, char *str)
{
	size_t	i;
	size_t	j;
	size_t	signal;
	size_t	len;

	len = ft_strlen(str);
	j = -1;
	while (++j < len)
	{
		i = -1;
		while (++i < sizeof(char) * __CHAR_BIT__ * len)
		{
			signal = (str[j] >> i) & 1;
			if (signal == 0)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			usleep(500);
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t		server_pid;
	char		*str;

	if (argc != 3)
	{
		printf("Wrong number of entrees given\n");
		return (0);
	}
	str = argv[2];
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		printf("Wrong PID number\n");
		return (0);
	}
	if (kill(server_pid, 0) < 0)
	{
		printf("Wrong server PID\n");
		return (0);
	}
	ft_send_strlength(server_pid, str);
	ft_send_str(server_pid, str);
	return (0);
}

// SIGUSR1 - this signal is understood as the 0-bit
// SIGUSR2 - this signal is understood as the 1-bit

	// printf("j = %zu, i = %zu\n", j, i);

	// printf("strlen = %lu\n", len);
	// printf("sizeof(int) = %lu bytes\n", sizeof(int));
	// printf("sizeof(size_t) = %lu bytes\n", sizeof(size_t));