/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:55:21 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/02 11:54:55 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"
#include "libft.h"

int	builtin_env(char **argv, t_min *ms)
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
