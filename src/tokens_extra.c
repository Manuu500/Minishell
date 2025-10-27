/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:50:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/27 18:07:19 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	check_if_pipes(char *input, int i, t_token *head, t_token *current)
// {
// 	if (input[i] == '|')
// 	{
// 		add_token(&head, &current, TOKEN_PIPE, "|");
// 		i++;
// 	}
// 	else if (input[i] == '<')
// 	{
// 		if (input[i + 1] == '<')
// 		{
// 			add_token(&head, &current, TOKEN_HEREDOC, "<<");
// 			i += 2;
// 		}
// 		else
// 		{
// 			add_token(&head, &current, TOKEN_REDIR_IN, "<");
// 			i++;
// 		}
// 	}
// 	else if (input[i] == '>')
// 	{
// 		if (input[i + 1] == '>')
// 		{
// 			add_token(&head, &current, TOKEN_REDIR_APPEND, ">>");
// 			i += 2;
// 		}
// 		else
// 		{
// 			add_token(&head, &current, TOKEN_REDIR_OUT, ">");
// 			i++;
// 		}
// 	}
// }
