/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:35:55 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/27 17:04:37 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	debug_token(t_token *head)
{
    t_token *current;
    int		i;

    current = head;
    i = 0;
    
    printf("\n=== DEBUG TOKENS ===\n");
    if (!current)
    {
        printf("ERROR: No hay tokens para mostrar (head es NULL)\n");
        printf("===================\n\n");
        return;
    }
    
    while (current)
    {
        printf("Token %d: Valor: '%s' Tipo: %u\n", i, current->value, current->type);
        current = current->next;
        i++;
    }
    printf("Total de tokens: %d\n", i);
    printf("===================\n\n");
}

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

static	void	add_token(t_token **head, t_token **current, t_token_type type, char *value)
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
			while (input [i] && input[i] != ' ' && input[i] != '\t' && input[i] != '<'
				&& input[i] != '>' && input[i] != '|')
				i++;
			if (i > start)
			{
				word = ft_substr(input, start, i - start);
				add_token(&head, &current, TOKEN_WORD, word);
				free(word);
			}
		}
	}
	return (head);
}


