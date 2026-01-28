/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_proc_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:52:30 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/28 12:42:25 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_quotes(char	*input, int i, char quote)
{
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (!input[i])
	{
		printf("No hay ningún input\n");
		return (-1);
	}
	return (i + 1);
}
