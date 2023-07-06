#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	signalHandler(int signal)
{
	if (signal == SIGUSR1)
		printf("Recibido bit = 0\n");
	if (signal == SIGUSR2)
		printf("Recibido bit = 1\n");
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
		sleep(1);
	return 0;
}
