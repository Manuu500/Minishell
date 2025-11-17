/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:07:51 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/17 13:23:49 by arivas-q         ###   ########.fr       */
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
int		command_dispatcher(t_command *command, t_minishell *ms);
int		execute_external_command(char **argv, char **envp);
void	exec_from_path(char **argv, char **envp);

/* Redirs */
void redir_dispatcher(t_redirect redirs, t_command command);
void redir_infile(t_redirect redirs, t_command command);
void redir_outfile(t_redirect redirs, t_command command);
void redir_heredoc(t_redirect redirs, t_command command);
void redir_append(t_redirect redir, t_command command);

#endif
