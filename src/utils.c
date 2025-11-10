/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:49:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/06 16:53:54 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	init_vars(t_minishell *minishell, t_command *command, t_redirect *redirect)
{
	(void) redirect;
	minishell->envp = NULL;
	minishell->user_input = NULL;
	redirect->fd = -1;
	command->redirs = malloc(sizeof(t_command));
	// command->input = malloc(sizeof(char) * 200);
	command->argv = malloc(sizeof(char) * 200);
	// redirect->value = malloc(sizeof(char) * 200);
	
}

