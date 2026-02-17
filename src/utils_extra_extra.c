/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:36:49 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/17 12:18:26 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_com(t_command *com)
{
	com->next = malloc(sizeof(t_command));
	if (!com->next)
		return ;
	ft_memset(com->next, 0, sizeof(t_command));
	com->next->redirs = malloc(sizeof(t_redir));
	if (!com->next->redirs)
	{
		free(com->next);
		return ;
	}
	ft_memset(com->next->redirs, 0, sizeof(t_redir));
	com->next->in_fd = 0;
	com->next->out_fd = 1;
}

static t_token	*check_if_pipe(t_token *split)
{
	while (split && split->type != TOKEN_PIPE)
		split = split->next;
	return (split);
}

//	printf("Error: invalid syntax\n"); Esto puede que tengamos que quitarlo
void	err_token(t_command *com, t_min *min)
{
	printf("Error: invalid syntax\n");
	com->redir_error = 1;
	min->last_exit_code = 2;
}

void	pipe_tokens_to_command(t_token *token, t_command *com, t_min *min)
{
	t_token	*split;
	t_token	*next;

	if (!token || !com || !min)
		return ;
	if (token->type == TOKEN_PIPE)
		return (err_token(com, min));
	split = check_if_pipe(token);
	if (!split)
		return (move_tokens_to_command(token, com, min));
	next = split->next;
	if (!next || next->type == TOKEN_PIPE)
		return (err_token(com, min));
	split->next = NULL;
	next->prev = NULL;
	move_tokens_to_command(token, com, min);
	split->next = next;
	next->prev = split;
	if (!com->next)
		init_com(com);
	pipe_tokens_to_command(next, com->next, min);
}

int	is_redir(t_token *current)
{
	return (current->type == TOKEN_REDIR_OUT
		|| current->type == TOKEN_REDIR_IN
		|| current->type == TOKEN_REDIR_APPEND
		|| current->type == TOKEN_HEREDOC);
}
