/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:19:16 by eshana            #+#    #+#             */
/*   Updated: 2021/09/09 00:27:25 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_lock;

void	ft_sent_byte(char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		//ft_putstr_fd("|s|", 1);
		g_lock = 1;
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while(g_lock)
			pause();
		i--;
	}
}

void	ft_handler(int sig, siginfo_t *si, void *context)
{
	(void)si;
	(void)context;
	//ft_putstr_fd("|r|", 1);
	//ft_putnbr_fd(g_lock, 1);
	if (sig == SIGUSR1)
		g_lock = 0;
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	g_lock = 0;
	siginfo_t si;
	struct sigaction act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = ft_handler;
	sigset_t   set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	act.sa_mask = set;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);

	if (argc == 3)
	{
		i = 0;
		server_pid = ft_atoi(argv[1]);
		while (argv[2][i])
		{
			ft_sent_byte(argv[2][i], server_pid);
			i++;
		}
	}
	exit(EXIT_SUCCESS);
}