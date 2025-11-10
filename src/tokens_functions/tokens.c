/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:35:55 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/10 16:27:17 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static	char	*check_var_token(t_minishell *minishell, char *str)
{
	char		*word;

	word = find_var_in_matrix(str, minishell);
	return (word);
}

static char	*substr_remove_quotes(char *input, int start, int len, char quote_type)
{
	char		*str;
	int			i;
	int			j;
	
	i = start;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	j = 0;
	while (i < start + len)
	{
		if (input[i] != quote_type)
		{
			str[j] = input[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

static void	save_var(char *input, t_token **head, t_token **current, t_minishell *minishell)
{
	int		count;
	char	*str;
	char	*result;
	int		i;

	i = 0;
	(void) current;
	str = NULL;
	result = NULL;
	count = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			while (input[i] >= 'A' && input[i] <= 'Z')
				i++;	
			str = ft_substr(input, 1, i - 0);
			result = check_var_token(minishell, str);
			add_token(head, current, TOKEN_VAR, result);
			free(str);
		}
		i++;
	}
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
		new_token->prev = NULL;
	}
	else
	{
		(*current)->next = new_token;
		new_token->prev = *current;
		*current = new_token;
	}
}

t_token	*tokenize(char *input, t_minishell *minishell)
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
		else if (input[i] == '$')
		{
			save_var(input, &head, &current, minishell);
			i++;
		}
		else
		{
			start = i;
			while (input[i])
			{
				if (input[i] == '\'' || input[i] == '\"')
				{
					quote = input[i];
					i++;
					while (input[i] && input[i] != quote)
						i++;
					if (!input[i])
					{
						printf("ERROR");
						return(NULL);
					}
					i++;
				}
				else if ((input[i] == ' ' || input[i] == '\t' || input[i] == '<'
					|| input[i] == '>' || input[i] == '|'))
					break;
				else
					i++;
			}
			if (i > start)
			{
				word = substr_remove_quotes(input, start, i - start, quote);
				add_token(&head, &current, TOKEN_WORD, word);
				free(word);
			}
		}
	}
	return (head);
}
