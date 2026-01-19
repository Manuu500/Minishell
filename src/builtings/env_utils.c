/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:26:39 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/19 13:17:28 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "../minishell.h"
#include "builtings.h"
#include <stdlib.h>
#include "libft.h"

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

char	**sort_env(char **envp)
{
	int		i;
	int		count;
	char	**sorted;

	i = 0;
	count = 0;
	while (envp[count])
		count++;
	sorted = dup_env(envp, count);
	sort_env_bubble(sorted, count);
	return (sorted);
}

void	print_export_format(const char *env)
{
	int	i;

	i = 0;
	printf("declare -x ");
	   while (env[i] && env[i] != '=')
		   ft_putchar_fd(env[i++], 1);
	   if (env[i] == '=')
		   printf("=\"%s\"\n", env + i + 1);
	   else
		   printf("\n");
}
