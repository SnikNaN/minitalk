/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:19:16 by eshana            #+#    #+#             */
/*   Updated: 2021/09/12 16:21:55 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_confirm;

static void	ft_send_byte(char c, int pid)
{
	int	i;
	int	tmp;

	i = 0;
	while (i < 8)
	{
		tmp = g_confirm;
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		if (tmp == g_confirm)
			sleep(1);
		if (tmp == g_confirm)
		{
			ft_putstr_fd("\nError: Server doesn't respond\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	ft_handler(int sig, siginfo_t *si, void *context)
{
	(void)sig;
	(void)si;
	(void)context;
	g_confirm++;
}

static void	ft_set_signals(void)
{
	struct sigaction	act;
	sigset_t			set;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = ft_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	act.sa_mask = set;
	sigaction(SIGUSR1, &act, 0);
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;

	ft_set_signals();
	if (argc == 3)
	{
		i = 0;
		server_pid = ft_atoi(argv[1]);
		if (!server_pid)
		{
			ft_putstr_fd("Error: Invalid PID\n", 2);
			exit(EXIT_FAILURE);
		}
		while (argv[2][i])
		{
			ft_send_byte(argv[2][i], server_pid);
			i++;
		}
		ft_putstr_fd("\nYour message has been sent.\n", 1);
		ft_putnbr_fd(i * 8, 1);
		ft_putstr_fd(" / ", 1);
		ft_putnbr_fd(g_confirm, 1);
		ft_putstr_fd("\n", 1);
		exit(EXIT_SUCCESS);
	}
	ft_putstr_fd("Error: Invalid arguments.\nUsage: ./client PID message\n", 2);
	exit(EXIT_FAILURE);
}
