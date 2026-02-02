/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:25:12 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/02 11:54:55 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../signals/signals.h"

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

static void	exec_child(t_command *cmd, char **envp, t_min *ms)
{
	char	**argv;

	argv = cmd->argv;
	apply_child_redirs(cmd);
	if (ft_strchr(argv[0], '/'))
	{
		execve(argv[0], argv, envp);
		write(2, "execve: error\n", 14);
		exit_program(ms, 127);
	}
	exec_from_path(argv, envp, ms);
}

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
