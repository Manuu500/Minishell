/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_proc_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:52:30 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/17 11:19:15 by mruiz-ur         ###   ########.fr       */
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
