/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:27 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/18 12:40:42 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <stdlib.h>

/* Exit built-in funcionality */
int	builtin_exit(char **argv, t_min *ms)
{
	if (!argv || !argv[1])
	{
		ms->run = 0;
	}
	return (0);
}
