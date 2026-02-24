/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:27 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/24 16:07:10 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <stdlib.h>

/* Check if argv[1] is a number or valid space */
static int	digit_check(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] == ' ' || argv[i] == '\t' || argv[i] == '\n'
		|| argv[i] == '\v' || argv[i] == '\f' || argv[i] == '\r')
		i++;
	if (argv[i] == '-' || argv[i] == '+')
		i++;
	if (!ft_isdigit(argv[i]))
		return (1);
	while (ft_isdigit(argv[i]))
		i++;
	while (argv[i] == ' ' || argv[i] == '\t' || argv[i] == '\n'
		|| argv[i] == '\v' || argv[i] == '\f' || argv[i] == '\r')
		i++;
	if (argv[i] == '\0')
		return (0);
	return (1);
}

/* Exit built-in funcionality */
int	builtin_exit(char **argv, t_min *ms)
{
	int	i;

	i = 0;
	if (!argv || !argv[1])
	{
		ms->run = 0;
	}
	else if (argv[1] && !argv[2] && (digit_check(argv[1]) == 0))
	{
		ms->run = 0;
		return (ft_atoi(argv[1]));
	}
	else if (argv[2] || (digit_check(argv[1]) == 1))
	{
		if (argv[2])
			printf("bash: exit: too many arguments\n");
		else if (digit_check(argv[1]) == 1)
			printf("bash: exit: numeric argument required\n");
	}
	return (0);
}
