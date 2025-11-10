/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/10 17:29:09 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_command command;
	t_minishell minishell;
	t_redirect	redirect;
	t_token	*tokens;
	(void) argv;
	(void) argc;
	
	while (1)
	{
		init_vars(&minishell, &command, &redirect);
		minishell.user_input = readline("Prompt: ");
		printf("Linea: %s\n", minishell.user_input);
		minishell.envp = copy_matrix(envp);
		tokens = tokenize(minishell.user_input, &minishell);
		// syntax_check(&command, tokens, &redirect);
		save_command(&command, &minishell);
		// debug_matrix_copy(&minishell);
		debug_token(tokens);
		safe_free(&minishell, &command);
	}
	return(1);
}
