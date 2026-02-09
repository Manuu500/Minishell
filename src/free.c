/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:05:20 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/09 16:28:46 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	free_minishell(t_min *ms)
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
	DELETED (sustituido en main por free_matrix)*/

static void	free_command(t_command *command)
{
	if (command->redirs)
		free_com_redirs(command);
	if (command->argv)
		free_com_argv(command);
}

static void	free_opt(t_opt_data *opt)
{
	t_redir	*r;
	t_redir	*nr;

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
	t_token	*t;
	t_token	*tn;

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

void	safe_free(t_min *min, t_command *com, t_opt_data *opt, t_token *token)
{
	if (min->user_input)
	{
		free(min->user_input);
		min->user_input = NULL;
	}
	if (com)
		free_command(com);
	if (opt)
		free_opt(opt);
	if (token)
		free_token(token);
}
