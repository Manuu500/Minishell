/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/17 16:35:01 by arivas-q         ###   ########.fr       */
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
	t_optimize_data	optimize_data;
	
	(void) argv;
	(void) argc;
	while (1)
	{
		init_vars(&minishell, &command, &redirect, &optimize_data);
		minishell.user_input = readline("Prompt: ");
		printf("Linea: %s\n", minishell.user_input);
		minishell.envp = copy_matrix(envp);
		tokens = tokenize(minishell.user_input, &minishell, &optimize_data);
		// syntax_check(&command, tokens, &redirect);
		save_command(&command, &minishell);
		command_dispatcher(&command, &minishell);
		// debug_matrix_copy(&minishell);
		//debug_token(tokens);//
		safe_free(&minishell, &command);
	}
	return(1);
}
