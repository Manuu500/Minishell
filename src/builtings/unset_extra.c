/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:36:41 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/22 20:37:15 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtings.h"

int	loop_key_match(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (key_match(envp[i], key))
			return (1);
		i++;
	}
	return (0);
}
