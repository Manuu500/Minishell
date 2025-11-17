/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:42:01 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/17 13:32:48 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"
#include "../minishell.h"

void redir_infile(t_redirect *r, t_command *cmd)
{
    int fd = open(r->filename, O_RDONLY);
    if (fd < 0)
    {
        perror(r->filename);
        return;
    }
    cmd->in_fd = fd;
}

void redir_outfile(t_redirect *r, t_command *cmd)
{
    int fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror(r->filename);
        return;
    }
    cmd->out_fd = fd;
}
void redir_append(t_redirect *r, t_command *cmd)
{
    int fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror(r->filename);
        return;
    }
    cmd->out_fd = fd;
}
