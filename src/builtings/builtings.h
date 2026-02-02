/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:08:15 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/02 11:54:55 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H
# include "../minishell.h"

int		is_builtin(char **argv);
int		builtin_dispatch(char **argv, t_min *ms);
int		builtin_export(char **argv, t_min *ms);
int		builtin_unset(char **argv, t_min *ms);
char	**sort_env(char **envp);
void	print_export_format(const char *env);
char	*join_key_value(const char *key, const char *value);

char	**add_env_var(char **envp, const char *key, const char *value);
char	**add_var_if_not_exists(char **envp, const char *key, const char *val);

int		builtin_echo(char **argv);
int		builtin_cd(char **argv, t_min *ms);
int		builtin_pwd(char **argv);
int		builtin_export(char **argv, t_min *ms);
int		builtin_env(char **argv, t_min *ms);
int		builtin_exit(char **argv, t_min *ms);

#endif