/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:36:49 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/12 12:49:31 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	check_if_pipe(t_token *split, t_token *token, t_command *com, t_minishell *min)
{
	while (split && split->type != TOKEN_PIPE)
		split = split->next;
	if (!split)
	{
		move_tokens_to_command(token, com, min);
		return ;
	}
}

static void init_pipes_vars(t_command *com)
{
	com->next->in_fd = 0;
	com->next->out_fd = 1;
	com->next->redirs->fd = -1;
	com->next->redirs->filename = NULL;
	com->next->redirs->next = NULL;
	com->next->redirs->type = 0;
	com->next->argv = NULL;
	com->next->redir_error = 0;
	com->next->next = NULL;
}

void	pipe_tokens_to_command(t_token *token, t_command *com, t_minishell *min)
{
	t_token *split;
	t_token *next_split;

	split = token;
	next_split = NULL;
	if (!token || !com || !min)
		return ;
	check_if_pipe(split, token, com, min);
	next_split = split->next;
	split->next = NULL;
	if (next_split)
		next_split->prev = NULL;
	move_tokens_to_command(token, com, min);
	if (!next_split)
		return ;
	if (!com->next)
	{
		com->next = malloc(sizeof(t_command));
		if (!com->next)
			return ;
		ft_memset(com->next, 0, sizeof(t_command));
		init_pipes_vars(com);
	}
	pipe_tokens_to_command(next_split, com->next, min);
}
