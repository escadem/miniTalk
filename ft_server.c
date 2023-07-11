/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eescat-l <eescat-l@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:39:35 by ysoroko           #+#    #+#             */
/*   Updated: 2023/07/11 18:32:22 by eescat-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static int	ft_receive_len(char **str, int signal)
{
	static int	len = 0;
	static int	bit = 0;

	if (signal == SIGUSR2)
		len += ft_power(2, bit);
	if (++bit == __CHAR_BIT__ * sizeof(int))
	{
		*str = ft_calloc(len + 1, sizeof(char));
		if (!*str)
			exit (EXIT_FAILURE);
		bit = 0;
		len = 0;
		return (1);
	}
	return (0);
}

static int	ft_process(char **str, int c)
{
	static int	i = 0;

	(*str)[i] = c;
	i++;
	if (c == 0)
	{
		ft_printf("%sClient says:%s %s%s\n", KYEL, KGRN, *str, KNRM);
		free(*str);
		i = 0;
		return (0);
	}
	return (1);
}

static void	ft_receiving(int signal, siginfo_t *info, void *context)
{
	static int	c = 0;
	static int	bit = 0;
	static int	received = 0;
	static char	*str = 0;

	if (!received)
		received = ft_receive_len(&str, signal);
	else
	{
		if (signal == SIGUSR2)
			c += ft_power(2, bit);
		if (++bit == __CHAR_BIT__ * sizeof(char)) 
		{
			received = ft_process(&str, c);
			c = 0;
			bit = 0;
		}
	}
}

void (*signal(int signum, void (*handler)(int)))(int);
void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	susr;

	susr.sa_sigaction = handler;
	susr.sa_flags = SA_SIGINFO | SA_NODEFER;
	sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("Server PID = %s%i%s\n", KYEL, pid, KNRM);
	init_sig(SIGUSR1, &ft_receiving);
	init_sig(SIGUSR2, &ft_receiving);
	while (1)
		sleep(1);
}

// [SIGUSR1] defines the '0' bit && [SIGUSR2] defines the '1' bit