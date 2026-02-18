/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:26:39 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/18 13:19:07 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "../minishell.h"
#include "builtings.h"
#include <stdlib.h>
#include "libft.h"

/* Create a dup for env to be sorted */
static char	**dup_env(char **envp, int count)
{
	char	**sorted;
	int		i;

	sorted = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count)
	{
		sorted[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted[i] = NULL;
	return (sorted);
}

/* Bubble sort for env */
static void	sort_env_bubble(char **sorted, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(sorted[j], sorted[j + 1], 100) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Main sort for export when no args */
char	**sort_env(char **envp)
{
	int		count;
	char	**sorted;

	count = 0;
	while (envp[count])
		count++;
	sorted = dup_env(envp, count);
	sort_env_bubble(sorted, count);
	return (sorted);
}

/* Export funcionality when no args */
void	print_export_format(const char *env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		printf("declare -x %.*s=\"%s\"\n", i, env, env + i + 1);
	else
		printf("declare -x %s\n", env);
}
