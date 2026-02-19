/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:32 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/19 13:09:25 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"

/* Env built-in funcionality */
int	builtin_env(char **argv, t_min *ms)
{
	int	i;

	(void)argv;
	if (!ms || !ms->envp)
		return (1);
	i = 0;
	while (ms->envp[i])
	{
		if (ft_strchr(ms->envp[i], '='))
			ft_putendl_fd(ms->envp[i], 1);
		i++;
	}
	return (0);
}
