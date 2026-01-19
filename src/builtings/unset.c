/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/19 13:08:11 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"

static int	key_match(const char *env, const char *key)
{
	int	i;

	i = 0;
	while (key[i] && env[i] && key[i] == env[i] && key[i] != '=')
		i++;
	if ((key[i] == 0 && env[i] == '=') || (key[i] == 0 && env[i] == 0))
		return (1);
	return (0);
}

char	**remove_env_var(char **envp, const char *key)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	i = 0;
	j = 0;
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (!key_match(envp[i], key))
			new_env[j++] = ft_strdup(envp[i]);
		i++;
	}
	new_env[j] = NULL;
	free_matrix(envp);
	return (new_env);
}

int	builtin_unset(char **argv, t_minishell *ms)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		ms->envp = remove_env_var(ms->envp, argv[i]);
		i++;
	}
	return (0);
}
