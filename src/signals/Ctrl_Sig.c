/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ctrl_Sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/19 11:33:06 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	on_sigint(int signum)
{
	(void)signum;
	if (g_in_child == SIGCTX_CHILD)
		return ;
	if (g_in_child == SIGCTX_HEREDOC)
	{
		g_in_child = SIGCTX_HEREDOC_INT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_done = 1;
		return ;
	}
	g_in_child = SIGCTX_PROMPT_INT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	on_sigquit(int signum)
{
	(void)signum;
	if (g_in_child == SIGCTX_CHILD)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

int	handle_ctrl_d(char *line, t_min *ms)
{
	if (line == NULL)
	{
		write(1, "exit\n", 5);
		ms->run = 0;
	}
	return (0);
}
