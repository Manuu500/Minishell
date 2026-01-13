/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:05:12 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/12 13:27:32 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <unistd.h>

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
	       if (i > 0 && prev[0] != -1 && (cmd->in_fd < 0 || cmd->in_fd == STDIN_FILENO))
		       dup2(prev[0], STDIN_FILENO);
	       if (i < n - 1 && next[1] != -1 && cmd->out_fd < 0)
		       dup2(next[1], STDOUT_FILENO);
	close_pair(prev);
	close_pair(next);
}

int wait_children(pid_t *pids, int n, int status)
{
	int i;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	return (status);
}
