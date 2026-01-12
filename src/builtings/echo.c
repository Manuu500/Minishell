/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:38 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/12 14:47:51 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"

int	builtin_echo(char **argv)
{
    int i;

    if (!argv)
        return (1);
    i = 1;
    while (argv[i])
    {
        ft_putendl_fd(argv[i], 1);
        i++;
    }
    return (0);
}
