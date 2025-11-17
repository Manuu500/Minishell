/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:46:36 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/17 13:01:42 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void add_redir_lst(t_redirect **head, char *value)
// {
// 	t_redirect *new_node;
// 	t_redirect *current;

// 	new_node = malloc(sizeof(t_redirect));
// 	if (!new_node)
// 		return ;
// 	new_node->value = value;
// 	new_node->next = NULL;
// 	if (*head == NULL)
// 		*head = new_node;
// 	else
// 	{
// 		current = *head;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new_node;
// 	}

// }

static	int	count_until_space(char *line)
{
	int	i;
	
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;		
	return (i);
}

void	save_command(t_command *command, t_minishell *minishell)
{
	int	i;
	char	*j;
	char	*k;

	i = 0;
	command->argv = ft_split(minishell->user_input, '|');
	while (command->argv[i])
	{
		j = ft_strchr(command->argv[i], '>');
		k = ft_strchr(command->argv[i], '<');
		if (j)
		{
			command->redirs->type = TOKEN_REDIR_OUT;
			j++;
			while (*j == ' ')
				j++;
			command->redirs->filename = ft_substr(j, 0, count_until_space(j));
		}
		if (k)
		{
			command->redirs->type = TOKEN_REDIR_IN;
			k++;
			while (*k == ' ')
				k++;
			command->redirs->filename = ft_substr(k, 0, count_until_space(k));
		}
		i = 0;
		if (command->redirs->next)
			command->redirs = command->redirs->next;
		i++;
	}
}
