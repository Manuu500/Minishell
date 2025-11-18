/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:42:01 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/18 12:05:40 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

void redir_infile(t_redirect *redirs, t_command *command)
{
    int fd;
	
	fd = open(redirs->filename, O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd(redirs->filename, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd("No such file or directory", 2);
        command->redir_error = 1;
        return;
    }
    if (command->in_fd != STDIN_FILENO)
        close(command->in_fd);
    command->in_fd = fd;
}

void redir_outfile(t_redirect *redirs, t_command *command)
{
    int fd;
	
	fd = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        ft_putstr_fd(redirs->filename, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd("Permission denied", 2);
        command->redir_error = 1;
        return;
    }
    if (command->out_fd != STDOUT_FILENO)
        close(command->out_fd);
    command->out_fd = fd;
}

void redir_append(t_redirect *redirs, t_command *command)
{
    int fd;
	
	fd = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        ft_putstr_fd(redirs->filename, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd("Permission denied", 2);
        command->redir_error = 1;
        return;
    }
    if (command->out_fd != STDOUT_FILENO)
        close(command->out_fd);
    command->out_fd = fd;
}

static int	create_heredoc_pipe(const char *delim, int *out_read_fd)
{
    int		fd[2];
    char	*line;

    if (pipe(fd) < 0)
        return (-1);
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
        {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    *out_read_fd = fd[0];
    return (0);
}

void	redir_heredoc(t_redirect *redirs, t_command *command)
{
    int	read_fd;

    if (create_heredoc_pipe(redirs->filename, &read_fd) < 0)
    {
        ft_putendl_fd("heredoc: error", 2);
        command->redir_error = 1;
        return;
    }
    if (command->in_fd != STDIN_FILENO)
        close(command->in_fd);
    command->in_fd = read_fd;
}