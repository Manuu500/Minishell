/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:35:55 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/27 18:22:19 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static	t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;
	
	if (!value)
		return(NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **head, t_token **current, t_token_type type, char *value)
{
	t_token	*new_token;
	
	new_token = create_token(type, value);
	if (!new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		*current = new_token;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;	
	}
}

t_token	*tokenize(char *input)
{
	t_token *head;
	t_token	*current;
	char	*word;
	char	quote;
	int		i;
	int		start;

	i = 0;
	head = NULL;
	current = NULL;
	if (!input)
		return(NULL);
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
            i++;
		if (!input[i])
			break;
		if (input[i] == '|')
		{
			add_token(&head, &current, TOKEN_PIPE, "|");
			i++;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&head, &current, TOKEN_HEREDOC, "<<");
				i += 2;
			}
			else
			{
				add_token(&head, &current, TOKEN_REDIR_IN, "<");
				i++;
			}
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&head, &current, TOKEN_REDIR_APPEND, ">>");
				i += 2;
			}
			else
			{
				add_token(&head, &current, TOKEN_REDIR_OUT, ">");
				i++;
			}
		}
		else
		{
			start = i;
			if (input[i] == 34 || input[i] == 39)
			{
				quote = input[i];
				i++;
				start++;
				while (input[i] && input[i] != quote)
					i++;
				if (!input[i])
				{
					printf("Error\n");
					return (NULL);
				}
				if (i > start)
				{
					word = ft_substr(input, start, i - start);
					add_token(&head, &current, TOKEN_WORD, word);
					free(word);
				}
				i++;
			}
			else
			{
				while (input [i] && input[i] != ' ' && input[i] != '\t' && input[i] != '<'
				&& input[i] != '>' && input[i] != '|' && input[i] != 39 && input[i] != 34)
					i++;
				if (i > start)
				{
					word = ft_substr(input, start, i - start);
					add_token(&head, &current, TOKEN_WORD, word);
					free(word);
				}
			}
		}
	}
	return (head);
}


