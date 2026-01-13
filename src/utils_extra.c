/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:10:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/13 13:17:06 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_mem(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

int	check_tokens(t_token *token)
{	
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void	tokens_to_command(t_token *tokens, t_command *com, t_minishell *min)
{
	int	is_pipe;
	
	is_pipe = check_tokens(tokens);
	if (is_pipe)
		pipe_tokens_to_command(tokens, com, min);
	else
		move_tokens_to_command(tokens, com, min);
}

void	exit_program(t_minishell *ms, int err_snipet)
{
	ms->last_exit_code = err_snipet;
	ms->run = 0;	
}