/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:35:52 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/18 15:40:19 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_com_redirs(t_command *com)
{
    t_redirect *r;
	t_redirect *nr;
    
    r = com->redirs;
    while (r)
    {
        nr = r->next;
        if (r->filename)
            free(r->filename);
        free(r);
        r = nr;
	}
    com->redirs = NULL;
}

void    free_com_argv(t_command *com)
{
    int i;
    i = 0;
    
    while (com->argv[i])
    {
        free(com->argv[i]);
        i++;
    }
    free(com->argv);
    com->argv = NULL;
}
