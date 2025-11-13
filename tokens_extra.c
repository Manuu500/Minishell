/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Manu <Manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:50:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/13 22:17:55 by Manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_pipe_token(char *input, t_optimize_data *optimize, int i)
{
	(void) input;
	add_token(&optimize->head, &optimize->current, TOKEN_PIPE, "|");
	return (i + 1);
}

int handle_input_redir(char *input, t_optimize_data *optimize, int i)
{
	if (input[i + 1] == '<')
	{
		add_token(&optimize->head, &optimize->current, TOKEN_HEREDOC, "<<");
		return (i + 2);
	}
	else
	{
		add_token(&optimize->head, &optimize->current, TOKEN_REDIR_IN, "<");
		return (i + 1);
	}
}

int	handle_output_redir(char *input, t_optimize_data *optimize, int i)
{
	if (input[i + 1] == '>')
	{
		add_token(&optimize->head, &optimize->current, TOKEN_REDIR_APPEND, ">>");
		return (i + 2);
	}
	else
	{
		add_token(&optimize->head, &optimize->current, TOKEN_REDIR_OUT, ">");
		return (i + 1);
	}
}

int handle_variable_token(char *input, t_optimize_data *optimize, int i, t_minishell *minishell)
{
    int start;
    char *str;
    char *result;

    start = i + 1;
    i++;
    while (input[i] >= 'A' && input[i] <= 'Z')
        i++;
    str = ft_substr(input, start, i - start);
    result = check_var_token(minishell, str);
    add_token(&optimize->head, &optimize->current, TOKEN_VAR, result);
    free(str);
    if (result)
        free(result);
    return (i);
}

int	process_word(char *input, int i, t_optimize_data *optimize)
{
	int		start;
	char	*word;
	char	quote;
	
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
				printf("No hay ningún input\n");
				return (-1);
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
		add_token(&optimize->head, &optimize->current, TOKEN_WORD, word);
		free(word);
	}
	return (i);
}
