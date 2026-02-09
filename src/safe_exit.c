// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   safe_exit.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/12/04 23:17:30 by vzurera-          #+#    #+#             */
// /*   Updated: 2026/02/02 09:29:49 by mruiz-ur         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h>
// #include <signal.h>

// void	__real_exit(int status);

// void	__wrap_exit(int status)
// {
// 	free((void *)-42);
// 	close(-42);
// 	__real_exit(status);
// }

// static void	cleanup(void)
// {
// 	free((void *)-42);
// 	close(-42);
// }

// static void	handle_signal(int sig)
// {
// 	cleanup();
// 	signal(sig, SIG_DFL);
// 	raise(sig);
// }

// __attribute__((constructor))
// static void	init_signal_handlers(void)
// {
// 	signal(SIGTERM, handle_signal);
// 	signal(SIGINT, handle_signal);
// 	signal(SIGQUIT, handle_signal);
// 	signal(SIGHUP, handle_signal);
// 	atexit(cleanup);
// }
