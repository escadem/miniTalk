#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int		ft_power(int base, int exp)
{
	int	i;
	int	result;

	result = 1;
	i = 0;
	while (++i <= exp)
		result = result * base;
	return (result);
}

void	signalHandler(int signal)
{
	static size_t	i;
	static unsigned int	strlength;

	if (i < sizeof(size_t) * 8)
	{
		// printf("i = %d, strlength = %d\n", i, strlength);
		if (signal == SIGUSR1)
			i++;
			// printf("i = %d, Recibido bit = 0\n", i++);
		if (signal == SIGUSR2)
		{
			strlength = strlength + ft_power(2, i);
			// printf("i = %zu, Recibido bit = 1\n", i);
			i++;
		}
			// printf("i = %d, Recibido bit = 1\n", i++);
		// printf("i = %zu, strlength = %d\n", i, strlength);
	}
	printf("La longitud de la cadena es %d\n", strlength);
	if (i < sizeof(char) * 8)
	{
		
	}
	if (i == sizeof(size_t) * 8)
	{
		strlength = 0;
		i = 0;
	}
	usleep(100);
}


int	main()
{
	pid_t	server_pid;

	server_pid = getpid();
	printf("El PID del programa servidor es: %d\n", server_pid);
	//
	printf("Esperando señales...\n");
	signal(SIGUSR1, signalHandler);
	signal(SIGUSR2, signalHandler);
	while (1)
		usleep(1);
	return 0;
}
