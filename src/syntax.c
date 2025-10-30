/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:46:36 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/30 18:21:32 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_check(t_minishell *minishell, t_token *token)
{
	(void) minishell;

	while (token)
	{
		
		// if (token->next && token->next->type == TOKEN_WORD)
		// 	printf("El siguiente es un texto\n");
		if (token->type != TOKEN_WORD && token->next->type != TOKEN_WORD)
			printf("dos pipes seguidos\n");
		// printf("Token: su valor es: %s y su tipo es %u\n", token->value, token->type);
		token = token->next;
	}
}