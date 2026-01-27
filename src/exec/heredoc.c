/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:36:30 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/27 11:23:02 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

static int	create_heredoc(const char *delim, int *out_fd, t_minishell *ms)
{
	int		fd[2];
	char	*line;
	char	*expanded;

	if (pipe(fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_variables(line, ms);
		write(fd[1], expanded, ft_strlen(expanded));
		write(fd[1], "\n", 1);
		free(expanded);
		free(line);
	}
	close(fd[1]);
	*out_fd = fd[0];
	return (0);
}

void	redir_heredoc(t_redirect *redirs, t_command *command, t_minishell *ms)
{
	int	read_fd;

	if (create_heredoc(redirs->filename, &read_fd, ms) < 0)
	{
		ft_putendl_fd("heredoc: error", 2);
		command->redir_error = 1;
		return ;
	}
	if (command->in_fd != STDIN_FILENO)
		close(command->in_fd);
	command->in_fd = read_fd;
}
