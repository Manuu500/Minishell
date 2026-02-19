/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:36:30 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/19 12:26:16 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include "../signals/signals.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/* Expands variables and writes one line to the pipe. */
static void	hd_write_line(int wfd, char *line, t_min *ms)
{
	char	*expanded;

	expanded = expand_variables(line, ms);
	write(wfd, expanded, ft_strlen(expanded));
	write(wfd, "\n", 1);
	free(expanded);
	free(line);
}

/* Child process: reads heredoc and writes to the pipe until delim/EOF. */
static void	hd_child_run(const char *delim, int fd[2], t_min *ms)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: ", 2);
			ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd((char *)delim, 2);
			ft_putendl_fd("')", 2);
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		hd_write_line(fd[1], line, ms);
	}
	exit(0);
}

/* Parent: waits child and returns a shell-like exit code. */
static int	hd_parent_wait(pid_t pid, int rfd, t_min *ms)
{
	int	status;
	int	ret;

	ret = 1;
	if (waitpid(pid, &status, 0) < 0)
	{
		close(rfd);
		return (1);
	}
	if (WIFSIGNALED(status))
		ret = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (ret == 130)
	{
		write(1, "\n", 1);
		ms->last_exit_code = 130;
		close(rfd);
	}
	return (ret);
}

/* Spawns heredoc reader child (Ctrl+C stops immediately) and returns fd. */
static int	create_heredoc(const char *delim, int *out_fd, t_min *ms)
{
	int		fd[2];
	pid_t	pid;
	int		ret;

	if (pipe(fd) < 0)
		return (-1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		close_pair(fd);
		setup_signal_handlers();
		return (-1);
	}
	if (pid == 0)
		hd_child_run(delim, fd, ms);
	close(fd[1]);
	ret = hd_parent_wait(pid, fd[0], ms);
	setup_signal_handlers();
	if (ret != 0)
		return (ret);
	*out_fd = fd[0];
	return (0);
}

/* Attaches heredoc fd as the command stdin. */
void	redir_heredoc(t_redir *redirs, t_command *command, t_min *ms)
{
	int	read_fd;
	int	ret;

	ret = create_heredoc(redirs->filename, &read_fd, ms);
	if (ret == 130)
	{
		command->redir_error = 1;
		return ;
	}
	if (ret < 0)
	{
		ft_putendl_fd("heredoc: error", 2);
		command->redir_error = 1;
		return ;
	}
	if (command->in_fd != STDIN_FILENO)
		close(command->in_fd);
	command->in_fd = read_fd;
}
