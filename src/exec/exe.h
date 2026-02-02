/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:07:51 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/02 11:47:33 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
# include <stddef.h>
# include "../minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pipe_ctx
{
	int			n;
	int			i;
	int			status;
	int			prev[2];
	int			next[2];
	pid_t		*pids;
	pid_t		pid;
	t_command	*cmd;
}	t_pipe_ctx;

/* Commands */
int		command_dispatcher(t_command *command, t_min *ms);
// int		execute_external_command(char **argv, char **envp);
int		execute_external_command(t_command *cmd, char **envp, t_min *ms);
void	exec_from_path(char **argv, char **envp, t_min *ms);
int		execute_pipeline(t_command *head, t_min *ms);
int		count_cmds(t_command *head);
void	close_pair(int p[2]);
int		wait_children(pid_t *pids, int n, int status);
int		run_pipeline_loop(t_pipe_ctx *ctx, t_min *ms);
void	init_state(t_pipe_ctx *ctx, t_command *head);
void	connect_child(t_pipe_ctx *ctx);
void	close_command_redir_fds(t_command *cmd);
/* Pipeline helpers (defined across pipes.c / pipe_loop.c) */
void	parent_after_fork(t_pipe_ctx *ctx);
void	apply_child_redirs_if_any(t_command *cmd);
int		abort_pipeline(t_pipe_ctx *ctx, int err);
int		handle_redirs_in_parent(t_command *cmd, t_min *ms);
void	exec_child_process(t_pipe_ctx *ctx, t_min *ms);

/* Redirs */
void	redir_dispatcher(t_command *command, t_min *ms);
void	redir_infile(t_redir *redirs, t_command *command);
void	redir_outfile(t_redir *redirs, t_command *command);
void	redir_append(t_redir *redirs, t_command *command);
void	redir_heredoc(t_redir *redirs, t_command *command, t_min *ms);
char	*expand_variables(char *line, t_min *ms);

#endif
