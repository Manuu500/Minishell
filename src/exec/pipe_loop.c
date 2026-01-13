/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:50:18 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/13 17:11:20 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../signals/signals.h"
#include "../builtings/builtings.h"

static int  safe_pipe(int next[2])
{
    if (pipe(next) == -1)
        return (1);
    return (0);
}

int handle_redirs_in_parent(t_command *cmd)
{
    if (cmd->redirs)
        redir_dispatcher(cmd);
    if (cmd->redir_error == 1)
        return (1);
    if (cmd->in_fd < 0)
        cmd->in_fd = STDIN_FILENO;
    if (cmd->out_fd < 0)
        cmd->out_fd = STDOUT_FILENO;
    return (0);
}

void exec_child_process(t_pipe_ctx *ctx, t_minishell *ms)
{
    execute_signals(SIGST_IN_CHILD, 0);
    connect_child(ctx->i, ctx->n, ctx->prev, ctx->next, ctx->cmd);
    apply_child_redirs_if_any(ctx->cmd);
    if (is_builtin(ctx->cmd->argv))
    {
        int status = builtin_dispatch(ctx->cmd->argv, ms);
        exit_program(ms, status);
    }
    exec_from_path(ctx->cmd->argv, ms->envp, ms);
    exit_program(ms, 127);
}

int run_pipeline_loop(t_pipe_ctx *ctx, t_minishell *ms)
{
    int status;

    execute_signals(SIGST_BEFORE_FORK, 0);
    status = 1;
    while (ctx->i < ctx->n)
    {
        if (handle_redirs_in_parent(ctx->cmd))
            return abort_pipeline(ctx, 1);
        if (ctx->i < ctx->n - 1 && safe_pipe(ctx->next))
            return abort_pipeline(ctx, 1);
        ctx->pid = fork();
        if (ctx->pid < 0)
            return abort_pipeline(ctx, 1);
        if (ctx->pid == 0)
            exec_child_process(ctx, ms);
        parent_after_fork(ctx);
        ctx->cmd = ctx->cmd->next;
        ctx->i++;
    }
    close_pair(ctx->prev);
    status = wait_children(ctx->pids, ctx->n, ctx->status);
    execute_signals(SIGST_AFTER_WAIT, status);
    return status;
}
