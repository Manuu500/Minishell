/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:29:08 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/18 12:04:47 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include "../builtings/builtings.h"

void redir_dispatcher(t_command *command)
{
	t_redirect	*redirs;

	redirs = command->redirs;
	while (redirs)
	{
		if (command->redir_error == 1)
			return;
		if (redirs->type == TOKEN_REDIR_IN)
			redir_infile(redirs, command);
		else if (redirs->type == TOKEN_REDIR_OUT)
			redir_outfile(redirs, command);
		else if (redirs->type == TOKEN_REDIR_APPEND)
			redir_append(redirs, command);
		else if (redirs->type == TOKEN_HEREDOC)
			redir_heredoc(redirs, command);
			
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
	if (command->redir_error == 1)
		return (0);
	if (is_builtin(cur_command))
		builtin_dispatch(cur_command, ms);
	else
		execute_external_command(cur_command, envp);
	if (command->next != NULL)
		(void)0; /* pipeline pendiente */
	return (1);
}

