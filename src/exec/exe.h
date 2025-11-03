/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:07:51 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/03 11:14:11 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H
# include <stddef.h>
# include "../minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

/* Commands */
int		command_dispatcher(t_token *token, t_minishell *ms);
int		execute_external_command(char **argv, char **envp);
void	exec_from_path(char **argv, char **envp);

/* Argv build */
size_t	argv_word_count(t_token *token);
char	**argv_from_tokens(t_token *token, size_t count);
char	**make_argv_view_from_tokens(t_token *token);

#endif
