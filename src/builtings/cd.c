/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:45 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/17 11:59:54 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <unistd.h>
#include <stdlib.h>

/* Search address in env */
static char	*get_env_value_local(char **envp, const char *key)
{
	int		i;
	size_t	key_len;

	if (!envp || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

/* Main cd built-in funcionality */
int	builtin_cd(char **argv, t_min *ms)
{
	char	*target;

	if (!ms)
		return (1);
	if (!argv || !argv[1])
	{
		target = get_env_value_local(ms->envp, "HOME");
		if (!target)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (1);
		}
	}
	else
		target = argv[1];
	if (chdir(target) != 0)
	{
		ft_putstr_fd("cd: cannot change directory\n", 2);
		return (1);
	}
	return (0);
}
