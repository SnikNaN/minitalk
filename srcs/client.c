/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:19:16 by eshana            #+#    #+#             */
/*   Updated: 2021/09/16 11:27:44 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_confirm;

static void	ft_print_res(int sent, int received)
{
	ft_putnbr_fd(sent, 1);
	ft_putstr_fd(" bits sent / ", 1);
	ft_putnbr_fd(received, 1);
	ft_putstr_fd(" confirmations received\n", 1);
	if (sent != received)
	{
		ft_putstr_fd("Error: Server doesn't respond\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("SUCCESS!\n", 1);
}

static void	ft_send_byte(char c, int pid, int cnt)
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
			usleep(20000);
		i++;
		if (tmp == g_confirm)
		{
			ft_print_res(cnt * 8 + i, g_confirm);
		}
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
			ft_send_byte(argv[2][i], server_pid, i);
			i++;
		}
		ft_print_res(i * 8, g_confirm);
		exit(EXIT_SUCCESS);
	}
	ft_putstr_fd("Error: Invalid arguments.\nUsage: ./client PID message\n", 2);
	exit(EXIT_FAILURE);
}
