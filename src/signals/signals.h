/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:28:03 by arivas-q          #+#    #+#             */
/*   Updated: 2026/02/19 11:36:05 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../minishell.h"

/* Etapas para la gestión de señales alrededor de la ejecución de un child */
typedef enum e_sigstage
{
	SIGST_BEFORE_FORK = 0,
	SIGST_IN_CHILD = 1,
	SIGST_AFTER_WAIT = 2
}	t_sigstage;

/*
 * g_in_child is used as signal context with these values:
 * - SIGCTX_IDLE: normal prompt.
 * - SIGCTX_CHILD: we are fork or in child.
 * - SIGCTX_PROMPT_INT: receive SIGINT in prompt.
 * - SIGCTX_HEREDOC: while reading heredoc.
 * - SIGCTX_HEREDOC_INT: receive SIGINT while heredoc.
 */
typedef enum e_sigctx
{
	SIGCTX_IDLE = 0,
	SIGCTX_CHILD = 1,
	SIGCTX_PROMPT_INT = 2,
	SIGCTX_HEREDOC = 3,
	SIGCTX_HEREDOC_INT = 4
}	t_sigctx;

/* Global VAR */
extern volatile sig_atomic_t	g_in_child;

void	setup_signal_handlers(void);
int		handle_ctrl_d(char *line, t_min *ms);

/* API de señales */
void	set_in_child(int val);
void	on_sigint(int signum);
void	on_sigquit(int signum);

/* Ejecuta la lógica de señales en la etapa indicada. Para SIGST_AFTER_WAIT,
   pasar el código de retorno (por ejemplo 130/131) en `ret`. */
void	execute_signals(t_sigstage stage, int ret, t_min *ms);

#endif