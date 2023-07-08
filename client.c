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

int	main(int	argc, char** argv)
{
	pid_t	server_pid;
	size_t	len;
	size_t		signal;
	size_t		i;

	if (argc != 3)
	{
		printf("Numero de parametros de entrada erroneos\n");
		return 0;
	}
	len = ft_strlen(argv[2]);
	printf("strlen = %lu\n", len);
	printf("sizeof(int) = %lu bytes\n", sizeof(int));
	printf("sizeof(size_t) = %lu bytes\n", sizeof(size_t));
	server_pid = ft_atoi(argv[1]);
	i = -1;
	while (++i < sizeof(size_t) * 8)
	{
		signal = (len >> i) & 1;
		printf("server_pid = %d, signal = %lu\n",server_pid, signal);
		if (signal == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
	}	


	// server_pid = ft_atoi(argv[1]);
	// if (argv[2][0] == '0') 
	// 	kill(server_pid, SIGUSR1);
	// if (argv[2][0] == '1') 
	// 	kill(server_pid, SIGUSR2);

	// 	printf("Señal enviada correctamente\n");
	// else
	// {
	// 	printf("Error al enviar la señal\n");
	// 	return 0;
	// }
	return 0;
}