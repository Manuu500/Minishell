/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:29:08 by arivas-q          #+#    #+#             */
/*   Updated: 2025/12/01 23:22:58 by vboxuser         ###   ########.fr       */
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
	if (count_cmds(command) > 1)
	{
		return (execute_pipeline(command, ms));
	}
	if (is_builtin(cur_command))
		return (builtin_dispatch(cur_command, ms)), 1;
	return (execute_external_command(command, envp));
}

