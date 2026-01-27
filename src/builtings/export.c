/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:37:26 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/27 11:06:32 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <stdio.h>

static int	is_valid_key(const char *key)
{
	int	i;
	int	ok;

	i = 0;
	if (!key)
		return (0);
	ok = 0;
	if ((key[0] >= 'A' && key[0] <= 'Z') || (key[0] >= 'a' && key[0] <= 'z')
		|| key[0] == '_')
		ok = 1;
	if (!ok)
		return (0);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		ok = 0;
		if ((key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= '0' && key[i] <= '9')
			|| key[i] == '_')
			ok = 1;
		if (!ok)
			return (0);
		i++;
	}
	return (1);
}

static void	print_sorted_env(char **envp)
{
	char	**sorted;
	int		i;

	i = 0;
	sorted = sort_env(envp);
	while (sorted && sorted[i])
	{
		print_export_format(sorted[i]);
		i++;
	}
	free_matrix(sorted);
}

static char	*dup_key_part(const char *arg)
{
	int		len;
	char	*key;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	key = ft_substr(arg, 0, len);
	return (key);
}

static void	apply_export_arg(char *arg, t_minishell *ms)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	key = NULL;
	value = NULL;
	if (eq)
	{
		key = dup_key_part(arg);
		value = eq + 1;
	}
	if (!eq)
		key = ft_strdup(arg);
	if (key && is_valid_key(key) && eq)
		ms->envp = add_env_var(ms->envp, key, value);
	else if (key && is_valid_key(key))
		ms->envp = add_var_if_not_exists(ms->envp, key, value);
	free(key);
}

int	builtin_export(char **argv, t_minishell *ms)
{
	int	i;

	i = 1;
	if (!argv || !argv[1])
	{
		print_sorted_env(ms->envp);
		return (0);
	}
	while (argv[i])
	{
		apply_export_arg(argv[i], ms);
		i++;
	}
	return (0);
}
