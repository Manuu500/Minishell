/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:29:08 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/17 13:22:58 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include "../builtings/builtings.h"

void redir_dispatcher(t_redirect *command)
{
	t_redirect	*redirs;

	redirs = command->redirs;
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN)
			redir_infile(redirs, command);
		else if (redirs->type == TOKEN_REDIR_OUT)
			redir_outfile(redirs, command);
		else if (redirs->type == TOKEN_HEREDOC)
			redir_heredoc(redirs, command);
		else if (redirs->type == TOKEN_REDIR_APPEND)
			redir_append(redirs, command);
		redirs = redirs->next;
	}
}

int	command_dispatcher(t_command *command, t_minishell *ms)
{
    char    **cur_command;
    char    **envp;

    envp = ms->envp;
    cur_command = command->argv;
    if (command->redirs)
        redir_dispatcher(command);
    if (is_builtin(cur_command[0]))
        builtin_dispatch(cur_command[0], ms);
    else
        execute_external_command(cur_command, envp);
    if (command->next != NULL)
        /* lógica de las pipes (hay mas comandos) */
    return (1)
}

