/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/12 12:45:11 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec/exe.h"
#include "signals/signals.h"

int	main(int argc, char **argv, char **envp)
{
	t_command command;
	t_minishell minishell;
	t_token	*tokens;
	t_optimize_data	optimize_data;
	
	(void) argv;
	if (argc != 2)
	{
		setup_signal_handlers();
		while (1)
		{
			init_vars(&minishell, &command, &optimize_data);
			minishell.user_input = readline("Prompt: ");
			handle_ctrl_d(minishell.user_input);
			minishell.envp = copy_matrix(envp);
			tokens = tokenize(minishell.user_input, &minishell, &optimize_data);
			tokens_to_command(tokens, &command, &minishell);
			// move_tokens_to_command(tokens, &command, &minishell);
			save_filename_redirs(&command, tokens);
			command_dispatcher(&command, &minishell);
			safe_free(&minishell, &command, &optimize_data, tokens);
		}
	}
	return(1);
}
