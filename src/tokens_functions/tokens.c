/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:35:55 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/20 16:17:00 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*check_var_token(t_minishell *minishell, char *str)
{
	char		*word;

	word = find_var_in_matrix(str, minishell);
	if (!word)
		printf("\n");
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

// static int	save_var(char *input, t_token **head, t_token **current, t_minishell *minishell, int start)
// {
// 	int		count;
// 	char	*str;
// 	char	*result;
// 	int		i;
// 	int		valid_flag;
// 	int		end_flag;

// 	end_flag = 0;
// 	valid_flag = 0;
// 	i = start;
// 	str = NULL;
// 	result = NULL;
// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 		{
// 			count = i + 1;
// 			i++;
// 			while (input[i] >= 'A' && input[i] <= 'Z')
// 			{
// 				valid_flag = 1;
// 				i++;
// 			}
// 			if (input[i] == '\0')
// 				return (1);
// 			if (valid_flag == 1)
// 			{
// 				str = ft_substr(input, count, i - count);
// 				if (!str)
// 				{
// 					free(str);
// 					printf("No existe la variable");
// 				}
// 				result = check_var_token(minishell, str);
// 				add_token(head, current, TOKEN_VAR, result);
// 				free(str);
// 			}
// 			else
// 			{
// 				printf("Invalid variable\n");
// 				exit (0);
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }


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

t_token	*tokenize(char *input, t_minishell *minishell, t_optimize_data *optimize)
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
			break;
		if (input[i] == '|')
			i = handle_pipe_token(input, optimize, i);
		else if (input[i] == '<')
			i = handle_input_redir(input, optimize, i);
		else if (input[i] == '>')
			i = handle_output_redir(input, optimize, i);
		else if (input[i] == '$')
			i = handle_variable_token(input, optimize, i, minishell);
		else
			i = process_word(input, i, optimize);
	}
	return (optimize->head);
}
