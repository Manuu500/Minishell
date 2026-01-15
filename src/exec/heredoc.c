/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:36:30 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/15 12:06:31 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

static char  *check_if_correct(char *var)
{
    if (var)
        return (var);
    else
        return (ft_strdup(""));
}

static char *expand_variables(char *line, t_minishell *ms)
{
    int     start;
    char    *var_name;
    char    *var_value;
    int     i;
    
    i = 0;
	while (line[i])
    {
        if (line[i] == '$')
        {
            start = ++i;
            while (line[i] >= 'A' && line[i] <= 'Z')
                i++; 
            if (i > start && (var_name = ft_substr(line, start, i - start)))
            {
                var_value = check_var_token(ms, var_name);
                free(var_name); 
                return (check_if_correct(var_value));
            }
        }
        else
            i++;
    }
    return (ft_strdup(line));
}

static int	create_heredoc_pipe(const char *delim, int *out_read_fd, t_minishell *ms)
{
    int		fd[2];
    char	*line;
    char    *expanded;
    
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
        expanded = expand_variables(line, ms);
        write(fd[1], expanded, ft_strlen(expanded));
        write(fd[1], "\n", 1);
        free(expanded);
        free(line);
    }
    close(fd[1]);
    *out_read_fd = fd[0];
    return (0);
}

void	redir_heredoc(t_redirect *redirs, t_command *command, t_minishell *ms)
{
    int	read_fd;

    if (create_heredoc_pipe(redirs->filename, &read_fd, ms) < 0)
    {
        ft_putendl_fd("heredoc: error", 2);
        command->redir_error = 1;
        return;
    }
    if (command->in_fd != STDIN_FILENO)
        close(command->in_fd);
    command->in_fd = read_fd;
}