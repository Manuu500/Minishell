/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:08:15 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/05 10:30:44 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINGS_H
# define BUILTINGS_H
# include "../minishell.h"

int		is_builtin(const char *name);
int		builtin_dispatch(char **argv, t_minishell *ms);

/* builtins */
int	builtin_echo(char **argv);
int	builtin_cd(char **argv, t_minishell *ms);
int	builtin_pwd(char **argv);
/*int	builtin_export(char **argv, t_minishell *ms);
int	builtin_unset(char **argv, t_minishell *ms);*/
int	builtin_env(char **argv, t_minishell *ms);
int	builtin_exit(char **argv, t_minishell *ms);
#endif