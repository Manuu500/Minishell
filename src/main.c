/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/03 10:53:09 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec/exe.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell minishell;
	t_token	*tokens;
	(void) argv;
	(void) argc;
	
	init_vars(&minishell);
	minishell.user_input = readline("Prompt: ");
	// setup_signal_handlers(); // pendiente de implementar
	minishell.envp = copy_matrix(envp);
	tokens = tokenize(minishell.user_input);
	// ejecutar comando/pipeline simple
	command_dispatcher(tokens, &minishell);
	safe_free(&minishell);
	return(1);
}
