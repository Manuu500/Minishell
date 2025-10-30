/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/30 17:59:53 by mruiz-ur         ###   ########.fr       */
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
	printf("Linea: %s\n", minishell.user_input);
	minishell.envp = copy_matrix(envp);
	tokens = tokenize(minishell.user_input);
	syntax_check(&minishell, tokens);
	// debug_matrix_copy(&minishell);
	// debug_token(tokens);
	safe_free(&minishell);
	return(1);
}
