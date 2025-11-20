/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:46:36 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/20 15:25:15 by mruiz-ur         ###   ########.fr       */
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

// static	int	count_until_space(char *line)
// {
// 	int	i;
	
// 	i = 0;
// 	while (line[i] && line[i] != ' ')
// 		i++;		
// 	return (i);
// }
// static	void	manage_red_out(t_command *command, char *j)
// {
// 	command->redirs->type = TOKEN_REDIR_OUT;
// 	j++;
// 	while (*j == ' ')
// 		j++;
// 	command->redirs->filename = ft_substr(j, 0, count_until_space(j));
// }

// static	void	manage_red_in(t_command *command, char *k)
// {
// 	command->redirs->type = TOKEN_REDIR_IN;
// 	k++;
// 	while (*k == ' ')
// 		k++;
// 	command->redirs->filename = ft_substr(k, 0, count_until_space(k));
// }

// void	save_command(t_command *command, t_minishell *minishell)
// {
// 	int		i;
// 	char	*k;
// 	char	*j;
	
// 	(void) minishell;
// 	i = 0;
// 	// command->argv = ft_split(minishell->user_input, '|');
// 	while (command->argv[i])
// 	{
// 		j = ft_strchr(command->argv[i], '>');
// 		k = ft_strchr(command->argv[i], '<');
// 		if (j)
// 			manage_red_out(command, command->argv[i]);
// 		else if (k)
// 			manage_red_in(command, command->argv[i]);
// 		if (command->redirs->next)
// 			command->redirs = command->redirs->next;
// 		i++;
// 	}
// }

void	save_filename_redirs(t_command *command, t_token *head)
{
	t_token *current;
	
	current = head;
	while (current)
	{
		if ((current->type == TOKEN_REDIR_IN) && current->next && current->next->type == TOKEN_WORD)
		{
			command->redirs->type = TOKEN_REDIR_IN;
			command->redirs->filename = current->next->value;
		}
		else if ((current->type == TOKEN_REDIR_OUT) && current->next && current->next->type == TOKEN_WORD)
		{
			command->redirs->type = TOKEN_REDIR_OUT;
			command->redirs->filename = current->next->value;
		}
		current = current->next;
	}
}
