/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:55:21 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/19 13:17:28 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"
#include "libft.h"

int	builtin_env(char **argv, t_minishell *ms)
{
	int	i;

	i = 0;
	(void)argv;
	while (ms->envp && ms->envp[i])
	{
		printf("%s\n", ms->envp[i]);
		i++;
	}
	return (0);
}
