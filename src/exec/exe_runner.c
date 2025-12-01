/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:25:12 by arivas-q          #+#    #+#             */
/*   Updated: 2025/12/01 23:15:02 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../signals/signals.h"

static void	apply_child_redirs(t_command *cmd)
{
	if (cmd->in_fd >= 0 && cmd->in_fd != STDIN_FILENO)
		dup2(cmd->in_fd, STDIN_FILENO);
	if (cmd->out_fd >= 0 && cmd->out_fd != STDOUT_FILENO)
		dup2(cmd->out_fd, STDOUT_FILENO);
}

static void	exec_child(t_command *command, char **envp)
{
    char **argv;
	
	argv = command->argv;
    apply_child_redirs(command);
    if (ft_strchr(argv[0], '/'))
    {
        execve(argv[0], argv, envp);
        write(2, "execve: error\n", 14);
        _exit(127);
    }
    exec_from_path(argv, envp);
}

static int	wait_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
	{
		write(2, "waitpid: error\n", 15);
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_external_command(t_command *command, char **envp)
{
	pid_t	pid;
	int		ret;

	if (!command || !command->argv || !command->argv[0])
		return (1);
	execute_signals(SIGST_BEFORE_FORK, 0);
	pid = fork();
	if (pid < 0)
	{
		write(2, "fork: error\n", 12);
		set_in_child(0);
		return (1);
	}
	if (pid == 0)
	{
		execute_signals(SIGST_IN_CHILD, 0);
		exec_child(command, envp);
	}
	{
		ret = wait_child(pid);
		execute_signals(SIGST_AFTER_WAIT, ret);
		return (ret);
	}
}
