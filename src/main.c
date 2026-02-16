/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:39 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/16 11:35:20 by mruiz-ur         ###   ########.fr       */
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

static void	run_s(t_min *min, t_command *com, t_opt_data *opt, t_token *tokens)
{
	while (min->run)
	{
		init_vars(min, com, opt);
		min->user_input = readline("Prompt: ");
		if (g_in_child == 2)
		{
			min->last_exit_code = 130;
			g_in_child = 0;
		}
		if (min->user_input && *min->user_input)
			add_history(min->user_input);
		handle_ctrl_d(min->user_input, min);
		tokens = tokenize(min->user_input, min, opt);
		com->tokens = tokens;
		tokens_to_command(tokens, com, min);
		command_dispatcher(com, min);
		safe_free(min, com, opt, tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command	command;
	t_min		minishell;
	t_token		*tokens;
	t_opt_data	optimize_data;

	(void) argv;
	tokens = NULL;
	if (argc == 1)
	{
		ft_bzero(&minishell, sizeof(t_min));
		init_data(&minishell, envp);
		run_s(&minishell, &command, &optimize_data, tokens);
		clean_envp(&minishell);
		rl_clear_history();
	}
	return (1);
}
