/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/22 18:00:16 by mruiz-ur         ###   ########.fr       */
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
	if (!envp || !key || !*key || !*envp)
		return (envp);
	while (envp[count])
		count++;
	if (!count)
		return (envp);
	new_env = ft_calloc(count + 1, sizeof(char *));
	if (!new_env)
		return (envp);
	while (envp[i])
	{
		if (!key_match(envp[i], key))
		{
			new_env[j] = ft_strdup(envp[i]);
			if (!new_env[j])
			{
				free_matrix(new_env);
				return (envp);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_matrix(envp);
	return (new_env);
}

int	builtin_unset(char **argv, t_min *ms)
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
