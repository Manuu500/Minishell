/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/30 13:26:19 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell minishell;
	t_token	*tokens;
	(void) argv;
	(void) argc;
	
	init_vars(&minishell);
	minishell.user_input = readline("Prompt: ");
	setup_signal_hanslers();
	printf("Linea: %s\n", minishell.user_input);
	minishell.envp = copy_matrix(envp);
	tokens = tokenize(minishell.user_input);
	// debug_matrix_copy(&minishell);
	debug_token(tokens);
	safe_free(&minishell);
	return(1);
}
