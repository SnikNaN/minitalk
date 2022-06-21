/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:19:08 by eshana            #+#    #+#             */
/*   Updated: 2021/09/13 10:51:52 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_sig_handler(int sig, siginfo_t *si, void *context)
{
	static int	bits;
	static int	byte;
	static int	pid;

	(void)context;
	if (sig == SIGUSR1)
		byte += 1 << bits;
	bits++;
	if (bits == 8)
	{
		ft_putchar_fd((char)byte, 1);
		bits = 0;
		byte = 0;
	}
	if (si->si_pid != 0)
		pid = si->si_pid;
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;
	sigset_t			set;

	ft_putstr_fd("PID of server is: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = ft_sig_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act.sa_mask = set;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		pause();
	exit(EXIT_SUCCESS);
}
