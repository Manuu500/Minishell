/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:29:08 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/09 12:48:16 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "exe.h"
#include "../builtings/builtings.h"

void	redir_dispatcher(t_command *command, t_min *ms)
{
	t_redir	*redirs;

	redirs = command->redirs;
	while (redirs)
	{
		if (command->redir_error == 1)
			return ;
		if (redirs->type == TOKEN_REDIR_IN)
			redir_infile(redirs, command);
		else if (redirs->type == TOKEN_REDIR_OUT)
			redir_outfile(redirs, command);
		else if (redirs->type == TOKEN_REDIR_APPEND)
			redir_append(redirs, command);
		else if (redirs->type == TOKEN_HEREDOC)
			redir_heredoc(redirs, command, ms);
		redirs = redirs->next;
	}
}

static void	builtin_redirs(t_command *command, int *saved_in, int *saved_out)
{
	*saved_in = dup(STDIN_FILENO);
	*saved_out = dup(STDOUT_FILENO);
	if (command->in_fd != STDIN_FILENO)
		dup2(command->in_fd, STDIN_FILENO);
	if (command->out_fd != STDOUT_FILENO)
		dup2(command->out_fd, STDOUT_FILENO);
}

static void	reset_builtin_fds(t_command *command, int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	if (command->in_fd != STDIN_FILENO)
		close(command->in_fd);
	if (command->out_fd != STDOUT_FILENO)
		close(command->out_fd);
}

int	command_dispatcher(t_command *command, t_min *ms)
{
	char	**cur_command;
	int		saved_in;
	int		saved_out;

	cur_command = command->argv;
	if (command->redirs)
		redir_dispatcher(command, ms);
	if (command->redir_error == 1)
	{
		close_command_redir_fds(command);
		return (0);
	}
	if (count_cmds(command) > 1)
		return (execute_pipeline(command, ms));
	if (is_builtin(cur_command))
	{
		int status;
		
		builtin_redirs(command, &saved_in, &saved_out);
		status = builtin_dispatch(cur_command, ms);
		reset_builtin_fds(command, saved_in, saved_out);
		ms->last_exit_code = status;
		return (0);
	}
	return (execute_external_command(command, ms->envp, ms));
}
