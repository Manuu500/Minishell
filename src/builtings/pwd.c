/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:25:07 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/26 13:36:02 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"
#include <unistd.h>
#include <stdlib.h>

void	__real_free(void *ptr);

int	builtin_pwd(char **argv)
{
	char	*cwd;

	(void)argv;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("cwd: error", 2);
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	__real_free(cwd);
	return (0);
}
