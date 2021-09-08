/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eshana <eshana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:19:08 by eshana            #+#    #+#             */
/*   Updated: 2021/09/09 00:23:06 by eshana           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_sig_handler(int sig, siginfo_t *si, void *context)
{
	static int	power;
	static int	byte;

	(void)context;
	//ft_putstr_fd("|r|", 1);
	if (sig == SIGUSR1)
		byte += 1 << (7 - power);
	power++;
	if (power == 8)
	{
		ft_putchar_fd(byte, 1);
		power = 0;
		byte = 0;
	}
	kill(si->si_pid, SIGUSR1);
	//ft_putstr_fd("|s|", 1);
}

int	main(void)
{
	siginfo_t si;
	struct sigaction act;

	ft_putstr_fd("PID of server is: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = ft_sig_handler;
	sigset_t   set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	act.sa_mask = set;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
	{
		pause();
		usleep(10);
	}
	return (0);
}
