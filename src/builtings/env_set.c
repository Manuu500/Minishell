/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:26:42 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/19 13:09:47 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"
#include <string.h>
#include <stdlib.h>

/* Create var in envp if there is no var with same name*/
char	**add_var_if_not_exists(char **envp, const char *key, const char *val)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0
			&& (envp[i][key_len] == '=' || envp[i][key_len] == '\0'))
		{
			return (envp);
		}
		i++;
	}
	return (add_env_var(envp, key, val));
}

/* Give value to any var in envp */
char	*join_key_value(const char *key, const char *value)
{
	char	*tmp;
	char	*res;

	if (!value)
		return (ft_strdup(key));
	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

/*  */
static int	update_env_var(char **envp, const char *key, const char *new_var)
{
	int	i;
	int	updated;

	i = 0;
	updated = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& (envp[i][ft_strlen(key)] == '='
			|| envp[i][ft_strlen(key)] == '\0'))
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

/* Handle different env cases */
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
