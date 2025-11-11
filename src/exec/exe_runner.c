/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:25:12 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/06 16:42:59 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../signals/signals.h"

static void	exec_child(char **argv, char **envp)
{
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

int	execute_external_command(char **argv, char **envp)
{
	pid_t	pid;
	int		ret;

	if (!argv || !argv[0])
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
		exec_child(argv, envp);
	}
	{
		ret = wait_child(pid);
		execute_signals(SIGST_AFTER_WAIT, ret);
		return (ret);
	}
}
