/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:35:55 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/02 12:30:49 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_var_token(t_min *minishell, char *str)
{
	char		*word;

	word = find_var_in_matrix(str, minishell);
	return (word);
}

char	*substr_remove_quotes(char *input, int start, int len, char quote_type)
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

static	t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
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
	new_token->prev = NULL;
	new_token->var_name = NULL;
	return (new_token);
}

void	add_token(t_token **head, t_token **current,
		t_token_type type, char *value)
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

t_token	*tokenize(char *input, t_min *minishell, t_opt_data *optimize)
{
	int		i;

	i = 0;
	if (!input)
		exit(1);
	while (input[i])
	{
		if (i == -1)
			exit(1);
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
			i = handle_pipe_token(input, optimize, i);
		else if (input[i] == '<')
			i = handle_input_redir(input, optimize, i);
		else if (input[i] == '>')
			i = handle_output_redir(input, optimize, i);
		else
			i = process_word(input, i, optimize, minishell);
	}
	return (optimize->head);
}
