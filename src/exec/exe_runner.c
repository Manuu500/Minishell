/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:25:12 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/17 12:51:31 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../signals/signals.h"

/* Closes any non-stdio redirection fds stored in a command. */
void	close_command_redir_fds(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->in_fd >= 0 && cmd->in_fd != STDIN_FILENO)
	{
		close(cmd->in_fd);
		cmd->in_fd = STDIN_FILENO;
	}
	if (cmd->out_fd >= 0 && cmd->out_fd != STDOUT_FILENO)
	{
		close(cmd->out_fd);
		cmd->out_fd = STDOUT_FILENO;
	}
}

/* Applies a command's redirections to the current process (child side). */
static void	apply_child_redirs(t_command *cmd)
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

/* Executes the command in the forked child and exits on failure. */
static void	exec_child(t_command *cmd, char **envp, t_min *ms)
{
	char	**argv;

	argv = cmd->argv;
	apply_child_redirs(cmd);
	if (ft_strchr(argv[0], '/'))
	{
		execve(argv[0], argv, envp);
		write(2, "execve: error\n", 14);
		exit_program(ms, 127, cmd);
		exit(127);
	}
	exec_from_path(argv, envp, ms);
	if (cmd->redirs)
		free_com_redirs(cmd);
	if (cmd->argv)
		free_com_argv(cmd);
	if (ms->envp)
		free_matrix(ms->envp);
	if (ms->user_input)
		free(ms->user_input);
	if (cmd->tokens)
		free_token(cmd->tokens);
	exit(127);
}

/* Waits for a child pid and converts its status to a shell exit code. */
static int	wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

/* Forks and runs an external command, returning its exit status. */
int	execute_external_command(t_command *cmd, char **envp, t_min *ms)
{
	pid_t	pid;
	int		ret;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	execute_signals(SIGST_BEFORE_FORK, 0, ms);
	pid = fork();
	if (pid < 0)
	{
		write(2, "fork: error\n", 12);
		set_in_child(0);
		return (1);
	}
	if (pid == 0)
	{
		execute_signals(SIGST_IN_CHILD, 0, ms);
		exec_child(cmd, envp, ms);
	}
	close_command_redir_fds(cmd);
	ret = wait_child(pid);
	execute_signals(SIGST_AFTER_WAIT, ret, ms);
	return (ret);
}
