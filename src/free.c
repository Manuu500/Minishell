/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:05:20 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/18 15:40:10 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	free_minishell(t_minishell *ms)
{
	int i;

	i = 0;
	while (ms->envp[i])
	{
		free(ms->envp[i]);
		i++;
	}
	free(ms->envp);
	ms->envp = NULL;
}

static void	free_command(t_command *command)
{
	if (command->redirs)
		free_com_redirs(command);	
	if (command->argv)
		free_com_argv(command);
}

static void free_opt(t_optimize_data *opt)
{
	t_redirect *r;
	t_redirect *nr;
	
	if (opt->head_red)
	{
		r = opt->head_red;
		while (r)
		{
			nr = r->next;
			if (r->filename)
				free(r->filename);
			free(r);
			r = nr;
		}
		opt->head_red = NULL;
	}
}

static void	free_token(t_token *token)
{
	t_token *t;
	t_token *tn;
	
	t = token;
	while (t)
	{
		tn = t->next;
		if (t->value)
			free(t->value);
		if (t->var_name)
			free(t->var_name);
		free(t);
		t = tn;
	}
}

void	safe_free(t_minishell *minishell, t_command *command, t_optimize_data *opt, t_token *token)
{
	HISTORY_STATE *history;
	
	history = history_get_history_state();
	clear_history();
	if (history)
		free(history);	
	if (minishell->user_input)
	{
		free(minishell->user_input);
		minishell->user_input = NULL;
	}
	if (minishell->envp)
		free_minishell(minishell);
	if (command)
		free_command(command);
	if (opt)
		free_opt(opt);
	if (token)
		free_token(token);
	// else if (opt && opt->head)
	// {
	// 	t = opt->head;
	// 	while (t)
	// 	{
	// 		tn = t->next;
	// 		if (t->value)
	// 			free(t->value);
	// 		if (t->var_name)
	// 			free(t->var_name);
	// 		free(t);
	// 		t = tn;
	// 	}
	// 	opt->head = NULL;
	// 	opt->current = NULL;
	// }
}

