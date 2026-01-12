/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:36:49 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/12 13:03:03 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static void	check_if_pipe(t_token *split, t_token *token, t_command *com, t_minishell *min)
// {
// 	while (split && split->type != TOKEN_PIPE)
// 		split = split->next;
// 	if (!split)
// 	{
// 		move_tokens_to_command(token, com, min);
// 		return ;
// 	}
//

void	pipe_tokens_to_command(t_token *token, t_command *com, t_minishell *min)
{
	t_token *split;
	t_token *next_split;

	split = token;
	next_split = NULL;
	if (!token || !com || !min)
		return ;
	while (split && split->type != TOKEN_PIPE)
		split = split->next;
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
	{
		com->next = malloc(sizeof(t_command));
		if (!com->next)
			return ;
		ft_memset(com->next, 0, sizeof(t_command));
		com->next->in_fd = 0;
		com->next->out_fd = 1;
	}
	pipe_tokens_to_command(next_split, com->next, min);
}
