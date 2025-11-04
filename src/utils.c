/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:49:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/04 17:33:19 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	init_vars(t_minishell *minishell, t_command *command, t_redirect *redirect)
{
	minishell->envp = NULL;
	minishell->user_input = NULL;
	command->input = malloc(sizeof(char) * 200);
	command->arg = malloc(sizeof(char) * 200);
	redirect->value = malloc(sizeof(char) * 200);
	
}

