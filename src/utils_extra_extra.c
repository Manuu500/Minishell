/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:36:49 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/26 15:53:58 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_com(t_command *com)
{
	com->next = malloc(sizeof(t_command));
	if (!com->next)
		return ;
	ft_memset(com->next, 0, sizeof(t_command));
	com->next->redirs = malloc(sizeof(t_redirect));
    if (!com->next->redirs)
    {
        free(com->next);
        return ;
    }
    ft_memset(com->next->redirs, 0, sizeof(t_redirect));
	com->next->in_fd = 0;
	com->next->out_fd = 1;
}

static t_token	*check_if_pipe(t_token *split)
{
	while (split && split->type != TOKEN_PIPE)
		split = split->next;
	return (split);
}

void	pipe_tokens_to_command(t_token *token, t_command *com, t_minishell *min)
{
	t_token *split;
	t_token *next_split;

	split = token;
	next_split = NULL;
	if (!token || !com || !min)
		return ;
	split = check_if_pipe(split);
	if (!split)
	{
		move_tokens_to_command(token, com, min);
		return ;
	}
	next_split = split->next;
	split->next = NULL;
	if (next_split)
		next_split->prev = NULL;
	move_tokens_to_command(token, com, min);
	if (!next_split)
		return ;
	if (!com->next)
		init_com(com);
	pipe_tokens_to_command(next_split, com->next, min);
}

int is_word_or_arg(t_token *current)
{
	return (current->type == TOKEN_WORD || current->type == TOKEN_VAR);
}

int	is_redir(t_token *current)
{
	return (current->type == TOKEN_REDIR_IN 
			|| current->type == TOKEN_REDIR_APPEND
			|| current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_HEREDOC);
}
