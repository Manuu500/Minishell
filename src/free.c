/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:05:20 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/13 23:07:57 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	safe_free(t_minishell *minishell, t_command *command)
{
	(void)  command;
    
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->envp)
		free_matrix(minishell->envp);
}
