#include <stdio.h>
#include <signal.h>
#include <unistd.h>

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
	int		signal;

	if (argc != 3)
	{
		printf("Numero de parametros de entrada erroneos\n");
		return 0;
	}
	server_pid = ft_atoi(argv[1]);
	signal = ft_atoi(argv[2]);
	if (kill(server_pid, signal) == 0)
		printf("Señal enviada correctamente\n");
	else
	{
		printf("Error al enviar la señal\n");
		return 0;
	}
	return 0;
}