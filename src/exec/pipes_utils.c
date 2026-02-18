/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:05:12 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/18 14:51:42 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <unistd.h>
#include <sys/wait.h>

/* Initializes the pipeline context and resets all pipe fds/state. */
void	init_state(t_pipe_ctx *ctx, t_command *head)
{
	ctx->prev[0] = -1;
	ctx->prev[1] = -1;
	ctx->next[0] = -1;
	ctx->next[1] = -1;
	ctx->i = 0;
	ctx->status = 0;
	ctx->cmd = head;
}

/* Counts the number of commands in a linked list pipeline. */
int	count_cmds(t_command *c)
{
	int	n;

	n = 0;
	while (c)
	{
		n++;
		c = c->next;
	}
	return (n);
}

/* Closes both ends of a pipe pair if they are open. */
void	close_pair(int p[2])
{
	if (p[0] != -1)
		close(p[0]);
	if (p[1] != -1)
		close(p[1]);
}

/* Connects previous/next pipes to stdio in the child, then closes pipe fds. */
void	connect_child(t_pipe_ctx *ctx)
{
	if (ctx->i > 0 && ctx->prev[0] != -1
		&& (ctx->cmd->in_fd < 0 || ctx->cmd->in_fd == 0))
		dup2(ctx->prev[0], 0);
	if (ctx->i < ctx->n - 1 && ctx->next[1] != -1
		&& (ctx->cmd->out_fd < 0 || ctx->cmd->out_fd == 1))
		dup2(ctx->next[1], 1);
	close_pair(ctx->prev);
	close_pair(ctx->next);
}

/* Waits all children in the pipeline and returns the last command exit code. */
int	wait_children(pid_t *pids, int n, int status)
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
