/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/05 15:05:14 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec/exe.h"

int	main(int argc, char **argv, char **envp)
{
	t_command command;
	t_minishell minishell;
	t_redirect	redirect;
	t_token	*tokens;
	(void) argv;
	(void) argc;
	
	init_vars(&minishell, &command, &redirect);
	minishell.user_input = readline("Prompt: ");
	printf("Linea: %s\n", minishell.user_input);
	minishell.envp = copy_matrix(envp);
	tokens = tokenize(minishell.user_input);
	// debug_matrix_copy(&minishell);
	debug_token(tokens);
	safe_free(&minishell, &command);
	return(1);
}
