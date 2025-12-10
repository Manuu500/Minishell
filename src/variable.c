/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:38:43 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/12/10 12:28:14 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	int	count_tokens(t_token *current)
// {
// 	int		count;

// 	count = 0;
// 	while (current != NULL)
// 	{
// 		count++;
// 		current = current->next;
// 	}
// 	return (count);
// }

// void	save_vars(t_minishell *minishell, t_token *token)
// {
// 	t_token *current;
// 	char	*var_name;
// 	char	*var_content;
// 	int		var_name_length;
// 	int		var_content_length;
// 	int		i;
// 	char	*pos;
	
// 	var_name_length = 0;
// 	var_content_length = 0;
// 	pos = NULL;
// 	(void) minishell;
// 	current = token;
// 	i = count_tokens(current);
// 	if (i == 1)
// 	{
// 		i = 0;
// 		*pos = ft_strrchr(current->value, '=');
// 		var_name_length = pos - current->value;
// 		printf("Cantidad antes del =: %i\n", var_name_length);
// 	}
// 	else
// 		return ;
// }