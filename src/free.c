/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:05:20 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/06 15:39:41 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	safe_free(t_minishell *minishell, t_command *command)
{
	int	i;
	(void)  command;
    
	if (minishell->user_input)
		free(minishell->user_input);
	if (minishell->envp)
		free_matrix(minishell->envp);
	i = 0;
	// if (command->input)
    // {
    //     i = 0;
    //     while (command->input[i])
    //     {
    //         free(command->input[i]); 
    //         i++;
    //     }
    //     free(command->input);
    //     command->input = NULL;
    // }
    // if (command->argv)
    // {
    //     i = 0;
    //     while (command->argv[i])
    //     {
    //         free(command->argv[i]); 
    //         i++;
    //     }
    //     free(command->argv);
    //     command->argv = NULL;
    // }
}
