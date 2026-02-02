/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:44:36 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/02 11:54:55 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "../minishell.h"

volatile sig_atomic_t	g_in_child = 0;

void	set_in_child(int val)
{
	if (val)
		g_in_child = 1;
	else
		g_in_child = 0;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, on_sigint);
	signal(SIGQUIT, on_sigquit);
}

void	execute_signals(t_sigstage stage, int ret, t_min *ms)
{
	if (stage == SIGST_BEFORE_FORK)
	{
		set_in_child(1);
	}
	else if (stage == SIGST_IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (stage == SIGST_AFTER_WAIT)
	{
		ms->last_exit_code = ret;
		if (ret == 130)
		{
			write(1, "\n", 1);
		}
		else if (ret == 131)
		{
			write(1, "Quit (core dumped)\n", 20);
		}
		set_in_child(0);
	}
}
