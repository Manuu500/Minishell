/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:05:20 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/12/12 21:24:38 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void	free_list(t_optimize_data *opt)
// {
		
// }

void	safe_free(t_minishell *minishell, t_command *command, t_optimize_data *opt)
{
	t_redirect	*next_redir;
    t_redirect	*redir;
	int	i;
	
	(void) opt;
	if (minishell->user_input)
		free(minishell->user_input);
	// free_list(opt);
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
	if (!command)
		return ;
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
	redir = command->redirs;
	while (redir)
	{
		next_redir = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = next_redir;
	}
}
