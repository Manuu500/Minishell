/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:42:01 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/27 12:16:08 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	redir_infile(t_redirect *redirs, t_command *command)
{
	int	fd;

	fd = open(redirs->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(redirs->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("No such file or directory", 2);
		command->redir_error = 1;
		return ;
	}
	if (command->in_fd != STDIN_FILENO)
		close(command->in_fd);
	command->in_fd = fd;
}

void	redir_outfile(t_redirect *redirs, t_command *command)
{
	int	fd;

	fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(redirs->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("Permission denied", 2);
		command->redir_error = 1;
		return ;
	}
	if (command->out_fd != STDOUT_FILENO)
		close(command->out_fd);
	command->out_fd = fd;
}

void	redir_append(t_redirect *redirs, t_command *command)
{
	int	fd;

	fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd(redirs->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("Permission denied", 2);
		command->redir_error = 1;
		return ;
	}
	if (command->out_fd != STDOUT_FILENO)
		close(command->out_fd);
	command->out_fd = fd;
}
