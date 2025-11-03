/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:27 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/03 12:25:29 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <stdlib.h>

int	builtin_exit(char **argv, t_minishell *ms)
{
    int code;

    (void)ms;
    if (!argv || !argv[1])
        exit(0);
    code = ft_atoi(argv[1]);
    exit(code);
    return (0);
}

