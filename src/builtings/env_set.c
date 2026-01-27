/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:26:42 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/27 11:07:29 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"
#include <string.h>
#include <stdlib.h>

char	**add_var_if_not_exists(char **envp, const char *key, const char *val)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			return (envp);
		}
		i++;
	}
	return (add_env_var(envp, key, val));
}

char	*join_key_value(const char *key, const char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	res = NULL;
	if (value)
	{
		res = ft_strjoin(tmp, value);
	}
	if (!value)
	{
		res = ft_strdup(tmp);
	}
	free(tmp);
	return (res);
}

static int	update_env_var(char **envp, const char *key, const char *new_var)
{
	int	i;
	int	updated;

	i = 0;
	updated = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(new_var);
			updated = 1;
		}
		i++;
	}
	return (updated);
}

static char	**append_env_var(char **envp, const char *new_var, int count)
{
	int		j;
	char	**new_env;

	j = 0;
	new_env = malloc(sizeof(char *) * (count + 2));
	while (j < count)
	{
		new_env[j] = ft_strdup(envp[j]);
		j++;
	}
	new_env[count] = ft_strdup(new_var);
	new_env[count + 1] = NULL;
	free_matrix(envp);
	return (new_env);
}

char	**add_env_var(char **envp, const char *key, const char *value)
{
	int		i;
	int		updated;
	char	*new_var;
	char	**result;

	i = 0;
	new_var = join_key_value(key, value);
	while (envp[i])
		i++;
	updated = update_env_var(envp, key, new_var);
	if (!updated)
	{
		result = append_env_var(envp, new_var, i);
		free(new_var);
		return (result);
	}
	free(new_var);
	return (envp);
}
