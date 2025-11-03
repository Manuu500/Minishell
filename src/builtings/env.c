/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:32 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/03 12:25:35 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"

int	builtin_env(char **argv, t_minishell *ms)
{
    int i;

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

