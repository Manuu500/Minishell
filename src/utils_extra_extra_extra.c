/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_extra_extra.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:54:49 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/03 10:49:29 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_is_word(t_token *current)
{
	return (current->next->type == TOKEN_WORD);
}

int	word_or_var(t_token *current)
{
	return (current->type == TOKEN_WORD || current->type == TOKEN_VAR);
}

int	char_is_valid(char *input, int i)
{
	return ((input[i] >= 'A' && input[i] <= 'Z')
		|| (input[i] >= 'a' && input[i] <= 'z') || (input[i] == '_')
		|| (input[i] >= '0' && input[i] <= '9'));
}

void	join_word(t_opt_data *opt, int i, int start)
{
	join_strings(opt, i, start);
	add_token(&opt->head, &opt->current, TOKEN_WORD, opt->word);
	free(opt->word);
}
