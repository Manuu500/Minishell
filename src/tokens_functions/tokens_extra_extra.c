/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_extra_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 16:46:56 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/28 12:39:27 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*include_legit_variable(char *input, t_optimize_data *optimize, int i, t_minishell *minishell)
{
	int		start;
	char	*str;
	char	*result;
	int		flag;

	(void) optimize;
	flag = 0;
	start = i + 1;
	i++;
	if (input[i] == '?')
		return (ft_itoa(minishell->last_exit_code));
	while ((input[i] >= 'A' && input[i] <= 'Z')
		|| (input[i] >= 'a' && input[i] <= 'z') || (input[i] >= '0' && input[i] <= '9')
		|| input[i] == '_')
	{
		flag = 1;
		i++;
	}
	if (flag == 1)
	{
		str = ft_substr(input, start, i - start);
		result = check_var_token(minishell, str);
		free(str);
		return (result);
	}
	else
		return (NULL);
}
