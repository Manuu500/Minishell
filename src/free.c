/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:05:20 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/12/30 19:12:32 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void	free_list(t_optimize_data *opt)
// {
		
// }

void	safe_free(t_minishell *minishell, t_command *command, t_optimize_data *opt, t_token *token)
{
	// t_redirect	*next_redir;
    // t_redirect	*redir;
	t_redirect *r;
	t_redirect *nr;
	t_token *t;
	t_token *tn;
	int	i;
	
	(void) opt;
	if (minishell->user_input)
		free(minishell->user_input);
	i = 0;
	if (minishell->envp)
	{
		while (minishell->envp[i])
		{
			free(minishell->envp[i]);
			i++;
		}
		free(minishell->envp);
	}
	if (command)
	{
		if (command->redirs)
		{
			r = command->redirs;
			while (r)
			{
				nr = r->next;
				if (r->filename)
					free(r->filename);
				free(r);
				r = nr;
			}
			command->redirs = NULL;
		}
		if (command->argv)
		{
			i = 0;
			while (command->argv[i])
			{
				free(command->argv[i]);
				i++;
			}
			free(command->argv);
		}
	}
	if (opt)
	{
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
	if (token)
	{
		{
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
			if (opt)
			{
				if (opt->head == token)
					opt->head = NULL;
				if (opt->current == token)
					opt->current = NULL;
			}
		}
	}
}
