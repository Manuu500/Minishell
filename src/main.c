/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/11 12:56:41 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec/exe.h"
#include "signals/signals.h"

int	main(int argc, char **argv, char **envp)
{
	t_command command;
	t_minishell minishell;
	t_redirect	redirect;
	t_token	*tokens;
	(void) argv;
	(void) argc;
	
	while(1) {
	init_vars(&minishell, &command, &redirect);
	setup_signal_handlers();
	minishell.user_input = readline("Prompt: ");
	if (handle_ctrl_d(minishell.user_input))
		break;
	minishell.envp = copy_matrix(envp);
	tokens = tokenize(minishell.user_input);
	command_dispatcher(tokens, &minishell);
	//* debug_matrix_copy(&minishell);
	//*safe_free(&minishell, &command);*//
	}
	return(1);
}
