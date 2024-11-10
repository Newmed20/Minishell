/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjadid <mjadid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:30:21 by abmahfou          #+#    #+#             */
/*   Updated: 2024/11/10 10:00:25 by mjadid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	controlc_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	exit(130);
}



void	sighdl(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	exit(1);
}

void	sighdl2(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	// g_signal = 24;
	exit(24);
}

void	handle_signal_exit_status(int signum)
{
	if (signum == 3 || signum == 2)
	{
		exit_status = 128 + WTERMSIG(exit_status);
		if (exit_status == 129)
			exit_status = 1;
		if (exit_status == 131)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}