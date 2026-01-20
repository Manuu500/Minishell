/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:25:12 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/20 16:23:48 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include <unistd.h>

static char	*get_env_value(char **envp, const char *key)
{
	size_t	key_len;
	int		i;

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

static char	*join_path_cmd(const char *dir, const char *cmd)
{
	size_t	len;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	len = ft_strlen(dir) + 1 + ft_strlen(cmd) + 1;
	full_path = (char *)malloc(len);
	if (!full_path)
		return (NULL);
	full_path[0] = '\0';
	ft_strlcpy(full_path, dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

static void	free_strv(char **parts)
{
	int	i;

	i = 0;
	while (parts && parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static void	try_exec_dir(const char *dir, char **argv, char **envp)
{
	char	*full_path;

	full_path = join_path_cmd(dir, argv[0]);
	if (full_path)
	{
		execve(full_path, argv, envp);
		free(full_path);
	}
}

void exec_from_path(char **argv, char **envp, t_minishell *ms)
{
	char	*path;
	char	**parts;
	int		i;

	path = get_env_value(envp, "PATH");
	if (!path)
	{
		write(2, "minishell: PATH not set\n", 24);
		exit_program(ms, 127);
	}
	parts = ft_split(path, ':');
	if (!parts)
		exit_program(ms, 127);
	i = 0;
	while (parts[i])
	{
		try_exec_dir(parts[i], argv, envp);
		i++;
	}
	write(2, argv[0], ft_strlen(argv[0]));
	write(2, ": command not found\n", 20);
	exit_program(ms, 127);
	free_strv(parts);
}
