/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ctrl_Sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/28 10:30:43 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	on_sigint(int signum)
{
	(void)signum;
	if (g_in_child)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	on_sigquit(int signum)
{
	(void)signum;
	if (g_in_child)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

int	handle_ctrl_d(char *line, t_minishell *ms)
{
	if (line == NULL)
	{
		write(1, "exit\n", 5);
		ms->run = 0;
	}
	return (0);
}
