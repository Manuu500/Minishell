/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:38 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/18 14:15:03 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"

/* -n option in echo built-in */
static int	is_n_option(const char *arg)
{
	int	i;

	if (!arg)
		return (0);
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/* Main echo built-in funcionality */
int	builtin_echo(char **argv)
{
	int	i;
	int	no_newline;

	if (!argv)
		return (1);
	no_newline = 0;
	i = 1;
	while (argv[i] && is_n_option(argv[i]))
	{
		no_newline = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
