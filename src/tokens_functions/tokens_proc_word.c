/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_proc_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:52:30 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/12/09 17:22:27 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_quotes(char	*input, int i, char quote)
{

	// char	*word;
	
	i++;
	while (input[i] && input[i] != quote)
	{
		// if (input[i] == '$')
		// {
		// 	word = include_legit_variable(input, optimize, i, minishell);
		// 	if (!word)
		// 		return -1;
		// 	i++;
		// }
		i++;
	}
	if (!input[i])
	{
		printf("No hay ningún input\n");
		return (-1);
	}
	return (i + 1);
}
