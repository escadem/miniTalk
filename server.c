#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	signalHandler(int signal)
{
	if (signal == 0)
		printf("Señal capturada: %d\n", signal);
	else
		printf("Señal capturada: %d\n", signal);
}


int	main()
{
	pid_t	server_pid;
	server_pid = getpid();
	printf("El PID del programa servidor es: %d\n", server_pid);
	//
	printf("Esperando señales...\n");
	signal(SIGUSR1, signalHandler);
	// while (1)
	// {
	// 	// signal(SIGUSR1, signalHandler);
	// 	sleep(10);
	// }
	sleep(10);
	return 0;
}
