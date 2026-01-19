/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ctrl_Sig.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:00:00 by arivas-q          #+#    #+#             */
/*   Updated: 2026/01/19 15:47:24 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	on_sigint(int signum)
{
	(void)signum;

	if (in_child)
		return;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	on_sigquit(int signum)
{
	(void)signum;

	if (in_child)
		return;
	rl_on_new_line();
	rl_redisplay();
}

int handle_ctrl_d(char *line)
{
    if (line == NULL)
    {
        write(1, "exit\n", 5);
        // rl_clear_history();
        exit(0);
    }
    return (0);
}