/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:27 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/02 11:54:55 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <stdlib.h>

int	builtin_exit(char **argv, t_min *ms)
{
	(void)ms;
	if (!argv || !argv[1])
	{
		ms->run = 0;
	}
	return (0);
}
