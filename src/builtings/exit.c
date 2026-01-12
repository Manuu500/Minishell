/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:27 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/12 16:15:56 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <stdlib.h>

int	builtin_exit(char **argv, t_minishell *ms)
{
    // int code;

    (void)ms;
    if (!argv || !argv[1])
    {
        ms->run = 0;
    }
    // code = ft_atoi(argv[1]);
    // exit(code);
    return (0);
}

