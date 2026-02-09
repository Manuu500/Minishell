/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/09 12:42:19 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec/exe.h"
#include "signals/signals.h"

static void	init_data(t_min *min, char **envp)
{
	using_history();
	min->run = 1;
	min->envp = copy_matrix(envp);
	setup_signal_handlers();
}

static void	clean_envp(t_min *min)
{
	if (min->envp)
		free_matrix(min->envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	command;
	t_min		minishell;
	t_token		*tokens;
	t_opt_data	optimize_data;

	(void) argv;
	if (argc != 2)
	{
		ft_bzero(&minishell, sizeof(t_min));
		init_data(&minishell, envp);
		while (minishell.run)
		{
			init_vars(&minishell, &command, &optimize_data);
			minishell.user_input = readline("Prompt: ");
			if (minishell.user_input && *minishell.user_input)
				add_history(minishell.user_input);
			handle_ctrl_d(minishell.user_input, &minishell);
			tokens = tokenize(minishell.user_input, &minishell, &optimize_data);
			tokens_to_command(tokens, &command, &minishell);
			command_dispatcher(&command, &minishell);
			safe_free(&minishell, &command, &optimize_data, tokens);
		}
		clean_envp(&minishell);
		rl_clear_history();
	}
	return (1);
}
