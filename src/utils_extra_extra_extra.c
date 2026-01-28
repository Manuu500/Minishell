/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_extra_extra.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:54:49 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/28 12:34:43 by mruiz-ur         ###   ########.fr       */
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
