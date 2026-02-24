/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/23 14:19:33 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"

int	key_match(const char *env, const char *key)
{
	int	i;

	i = 0;
	while (key[i] && env[i] && key[i] == env[i] && key[i] != '=')
		i++;
	if ((key[i] == 0 && env[i] == '=') || (key[i] == 0 && env[i] == 0))
		return (1);
	return (0);
}

static int	get_env_len_and_idx(char **envp, char *key, int *idx)
{
	int	len;

	len = 0;
	*idx = -1;
	while (envp[len])
	{
		if (*idx < 0 && key_match(envp[len], key))
			*idx = len;
		len++;
	}
	return (len);
}

static char	**build_new_envp(char **envp, int len, int idx)
{
	int		i;
	int		j;
	char	**new_envp;

	new_envp = ft_calloc(len, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i != idx)
			new_envp[j++] = envp[i];
		i++;
	}
	new_envp[j] = NULL;
	free(envp[idx]);
	free(envp);
	return (new_envp);
}

int	remove_env_var(char ***envp, char *key)
{
	int		len;
	int		idx;
	char	**new_envp;

	if (!envp || !*envp || !key || !*key)
		return (0);
	len = get_env_len_and_idx(*envp, key, &idx);
	if (idx < 0)
		return (0);
	new_envp = build_new_envp(*envp, len, idx);
	if (!new_envp)
		return (126);
	*envp = new_envp;
	return (0);
}

int	builtin_unset(char **argv, t_min *ms)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (argv[i])
	{
		ret = remove_env_var(&ms->envp, argv[i]);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}
