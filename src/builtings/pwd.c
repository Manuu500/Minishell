/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:07 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/03 12:36:21 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <unistd.h>
#include <stdlib.h>

int	builtin_pwd(char **argv)
{
    char *cwd;

    (void)argv;
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        ft_putendl_fd("cwd: error", 2);
        return (1);
    }
    ft_putendl_fd(cwd, 1);
    free(cwd);
    return (0);
}
