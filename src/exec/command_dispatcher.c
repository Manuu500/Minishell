/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:29:08 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/05 10:19:38 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include "../builtings/builtings.h"

int	command_dispatcher(t_token *token, t_minishell *ms)
{
	char	**argv;
	int		status;

	if (!token || !ms)
		return (1);
	if (token->type != TOKEN_WORD)
		return (0);
	/* PIPELINE ???? */
	argv = make_argv_view_from_tokens(token);
	if (!argv)
		return (1);
	if (is_builtin(argv[0]))
	{
		status = builtin_dispatch(argv, ms);
		free(argv);
		return (status);
	}
	status = execute_external_command(argv, ms->envp);
	free(argv);
	return (status);
}
