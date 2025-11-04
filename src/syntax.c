/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:46:36 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/04 18:14:02 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_check(t_command *command, t_token *token, t_redirect *redirect)
{
	int	i_redir;
	int	j_arg;
	int	k_input;
	int	i;
	int	j;

	j = 0;
	i = 0;
	i_redir = 0;
	j_arg = 0;
	k_input = 0;
	if (!token)
		return ;
	while (token)
	{
		// printf("Token: su valor es: %s y su tipo es %u\n", token->value, token->type);
		/*
		si es palabra
			si no hay comando
				es comando
			si si
				es argumento
		si es pipe
			siguiente comando
		si es redireccion
			si siguiente no es palabra
				error
			añadir al final
		 
		*/
		if (token->type == TOKEN_WORD)
		{
			// if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_APPEND)
			// {
			// 	if (token->next->type)
			// 	redirect->value[i_redir] = token->next->value;
			// 	redirect->type = token->next->type;
			// 	i_redir++;
			// }
			if (command->input[0] && token->prev && 
				(token->prev->type != TOKEN_REDIR_OUT && 
				token->prev->type != TOKEN_REDIR_IN && 
				token->prev->type != TOKEN_REDIR_APPEND))
			{
				command->arg[j_arg] = token->value;
				j_arg++;
			}
			else if (!command->input[0])
			{
				command->input[k_input] = token->value;
				k_input++;
			}
		}
		else if (token->type == TOKEN_PIPE)
		{
			if (token->next && token->next->type == TOKEN_WORD)
			{
				command->input[k_input] = token->next->value;
				k_input++;
				token = token->next;
			}
		}
		else if (token->type != TOKEN_WORD)
		{
			if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || token->type == TOKEN_REDIR_APPEND)
			{
				if (token->next && token->next->type == TOKEN_WORD)
				{
					redirect->value[i_redir] = token->next->value;
					redirect->type = token->type;
					i_redir++;
					token = token->next;
				}
			}
			else if (token->next && token->next->type != TOKEN_WORD)
				printf("Hay dos pipes seguidos\n");
		}
		// else if (token->type != TOKEN_WORD && token->next->type != TOKEN_WORD)
		// 	printf("dos pipes seguidos\n");
		token = token->next;
	}
	//DEBUG
	printf("\n=== ESTADO FINAL ===\n");
    printf("command->input:\n");
    i = 0;
    while (command->input[i])
    {
        printf("  [%d]: %s\n", i, command->input[i]);
        i++;
    }
    
    printf("command->arg:\n");
    j = 0;
    while (command->arg[j])
    {
        printf("  [%d]: %s\n", j, command->arg[j]);
        j++;
    }
	
	printf("comand->redir:\n");
    j = 0;
    while (redirect->value[j])
    {
        printf("  [%d]: %s\n", j, redirect->value[j]);
        j++;
    }
    printf("==================\n\n");
}
