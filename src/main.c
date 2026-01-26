/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/26 14:03:57 by mruiz-ur         ###   ########.fr       */
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
		ft_bzero(&minishell, sizeof(t_minishell)); /*Nchange*/
		using_history();
		minishell.run = 1;
		minishell.envp = copy_matrix(envp); /*Nchange*/
		setup_signal_handlers();
		while (minishell.run)
		{
			// minishell.last_exit_code = 0;
			init_vars(&minishell, &command, &optimize_data);
			minishell.user_input = readline("Prompt: ");
			if (minishell.user_input && *minishell.user_input)
				add_history(minishell.user_input);
			handle_ctrl_d(minishell.user_input, &minishell);
			/*minishell.envp = copy_matrix(envp) DELETED*/
			tokens = tokenize(minishell.user_input, &minishell, &optimize_data);
			tokens_to_command(tokens, &command, &minishell);
			command_dispatcher(&command, &minishell);
			safe_free(&minishell, &command, &optimize_data, tokens);
		}
		if (minishell.envp) /*Nchange*/
			free_matrix(minishell.envp);/*Nchange*/
		rl_clear_history();
	}
	return(1);
}
