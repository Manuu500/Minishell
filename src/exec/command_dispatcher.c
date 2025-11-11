/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:29:08 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/11 18:12:52 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include "../builtings/builtings.h"

int redir_dispatcher(t_redirect redirs)
{
    redirs->fd = open(redirs->filename);
    if (!redirs->fd)
        
}

int	command_dispatcher(t_command *command, t_minishell *ms)
{
    char    **cur_command;
    char    **envp;

    envp = ms->envp;
    cur_command = command->argv;
    if (command->redirs)
        redir_dispatcher(command->redirs)
    if (is_builtin(cur_command[0]))
        builtin_dispatch(cur_command[0], ms);
    else
        execute_external_command(cur_command, envp);
    if (command->next != NULL)
        /* lógica de las pipes (hay mas comandos) */
    return (1)
}

