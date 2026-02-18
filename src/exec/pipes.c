/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:54:08 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/18 14:51:42 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/* Updates parent state after forking a pipeline child (close/shift pipe fds). */
void	parent_after_fork(t_pipe_ctx *ctx)
{
	ctx->pids[ctx->i] = ctx->pid;
	close_command_redir_fds(ctx->cmd);
	if (ctx->next[1] != -1)
	{
		close(ctx->next[1]);
		ctx->next[1] = -1;
	}
	close_pair(ctx->prev);
	ctx->prev[0] = ctx->next[0];
	ctx->prev[1] = -1;
	ctx->next[0] = -1;
}

/* Applies a command's redirection fds to stdio in the current process. */
void	apply_child_redirs_if_any(t_command *cmd)
{
	if (cmd->in_fd >= 0 && cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
		cmd->in_fd = STDIN_FILENO;
	}
	if (cmd->out_fd >= 0 && cmd->out_fd != STDOUT_FILENO)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
		cmd->out_fd = STDOUT_FILENO;
	}
}

/* Aborts pipeline execution, closes fds, frees pids, and returns err. */
int	abort_pipeline(t_pipe_ctx *ctx, int err)
{
	close_pair(ctx->prev);
	close_pair(ctx->next);
	close_command_redir_fds(ctx->cmd);
	if (ctx->pids)
		free(ctx->pids);
	return (err);
}

/* Initializes pipeline context and runs the pipeline loop for a command list. */
int	execute_pipeline(t_command *command, t_min *ms)
{
	int			n;
	t_pipe_ctx	ctx;

	n = count_cmds(command);
	if (n <= 1)
		return (0);
	ctx.pids = (pid_t *)malloc(sizeof(pid_t) * n);
	if (!ctx.pids)
		return (1);
	init_state(&ctx, command);
	ctx.n = n;
	return (run_pipeline_loop(&ctx, ms, command));
}
