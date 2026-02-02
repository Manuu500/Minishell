/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:58:38 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/02 12:36:04 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var_in_matrix(char *var, t_min *minishell)
{
	int		i;
	char	*content;
	char	*equal_pos;

	i = 0;
	content = NULL;
	while (minishell->envp[i])
	{
		if (ft_strncmp(minishell->envp[i], var, ft_strlen(var)) == 0)
		{
			equal_pos = ft_strchr(minishell->envp[i], '=');
			if (equal_pos)
			{
				content = ft_strdup(equal_pos + 1);
				return (content);
			}
		}
		i++;
	}
	return (NULL);
}
