/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:04:53 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/03 10:39:04 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Builtins API minimal: detección y dispatcher con argv completo
#include "builtings.h"

int	is_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

// Nota: Implementaciones reales de builtins no están aún.
// Devolvemos 0 para éxito por defecto; sustituir por llamadas reales.
int	builtin_dispatch(char **argv, t_minishell *ms)
{
	(void)ms;
	if (!argv || !argv[0])
		return (1);
	// Ejemplo de esqueleto (descomenta e implementa cuando estén listos):
	// if (ft_strncmp(argv[0], "echo", 5) == 0) return (builtin_echo(argv));
	// else if (ft_strncmp(argv[0], "cd", 3) == 0) return (builtin_cd(argv, ms));
	// ...
	return (0);
}