/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:16:16 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/27 15:10:58 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	count_envp(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**copy_matrix(char **envp)
{
	char		**envp_copy;
	int				count;
	int					i;
	
	if (!envp)
		return (NULL);
	count = count_envp(envp);
	envp_copy = malloc(sizeof(char *) * (count + 1));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
			free_matrix(envp_copy);
		i++;
	}
	envp_copy[i] = NULL;
	printf("Ha llegado bien");
	return(envp_copy);
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
