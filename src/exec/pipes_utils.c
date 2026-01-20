/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:05:12 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/20 18:21:27 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <unistd.h>
#include <sys/wait.h>

void init_state(t_pipe_ctx *ctx, t_command *head)
{
	ctx->prev[0] = -1;
	ctx->prev[1] = -1;
	ctx->next[0] = -1;
	ctx->next[1] = -1;
	ctx->i = 0;
	ctx->status = 0;
	ctx->cmd = head;
}

int	count_cmds(t_command *c)
{
	int n;

	n = 0;
	while (c)
	{
		n++;
		c = c->next;
	}
	return (n);
}

void	close_pair(int p[2])
{
	if (p[0] != -1)
		close(p[0]);
	if (p[1] != -1)
		close(p[1]);
}

void connect_child(int i, int n, int prev[2], int next[2], t_command *cmd)
{
	if (i > 0 && prev[0] != -1 && (cmd->in_fd < 0 || cmd->in_fd == 0))
		dup2(prev[0], 0);
	if (i < n - 1 && next[1] != -1 && (cmd->out_fd < 0 || cmd->out_fd == 1))
		dup2(next[1], 1);
	close_pair(prev);
	close_pair(next);
}

int wait_children(pid_t *pids, int n, int status)
{
	int	i;
	int	wstatus;
	int	last_wstatus;

	(void)status;
	i = 0;
	last_wstatus = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &wstatus, 0) >= 0 && i == n - 1)
			last_wstatus = wstatus;
		i++;
	}
	free(pids);
	if (WIFEXITED(last_wstatus))
		return (WEXITSTATUS(last_wstatus));
	if (WIFSIGNALED(last_wstatus))
		return (128 + WTERMSIG(last_wstatus));
	return (1);
}
