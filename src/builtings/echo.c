/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:38 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/17 11:58:27 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "builtings.h"

/* Ignore "-n" in echo built-in */
static int	ignore_n(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] && (ft_strncmp(argv[i], "-n", 2) == 0))
	{
		j = 1;
		while (argv[i][j] && argv[i][j] == 'n')
		{
			j++;
			if (argv[i][j] && argv[i][j] != 'n')
				return (i);
		}
		i++;
	}
	return (i);
}

/* Case "echo -n" where there is no \n */
static void	no_nl_echo(char **argv)
{
	int	i;

	i = ignore_n(argv);
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
}

/* Main echo built-in funcionality */
int	builtin_echo(char **argv)
{
	int	i;

	if (!argv)
		return (1);
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		no_nl_echo(argv);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
