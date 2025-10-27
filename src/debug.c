/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:47:07 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/27 17:48:06 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_token(t_token *head)
{
    t_token *current;
    int		i;

    current = head;
    i = 0;
    
    printf("\n=== DEBUG TOKENS ===\n");
    if (!current)
    {
        printf("ERROR: No hay tokens para mostrar (head es NULL)\n");
        printf("===================\n\n");
        return;
    }
    
    while (current)
    {
        printf("Token %d: Valor: '%s' Tipo: %u\n", i, current->value, current->type);
        current = current->next;
        i++;
    }
    printf("Total de tokens: %d\n", i);
    printf("===================\n\n");
}

void	debug_matrix_copy(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->envp)
		return ;
	while (minishell->envp[i])
	{
		printf("Linea de envp: %s\n", minishell->envp[i]);
		i++;
	}
}
