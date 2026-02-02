/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:32 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/02 11:54:55 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"

int	builtin_env(char **argv, t_min *ms)
{
	int	i;

	(void)argv;
	if (!ms || !ms->envp)
		return (1);
	i = 0;
	while (ms->envp[i])
	{
		ft_putendl_fd(ms->envp[i], 1);
		i++;
	}
	return (0);
}
