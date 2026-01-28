/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:50:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/28 12:41:55 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_word_to_com(char *word, t_command *com)
{
	int	i;
	int	word_lenght;

	word_lenght = ft_strlen(word);
	i = 0;
	com->argv = malloc(sizeof(char *) * word_lenght);
	if (!com->argv)
		return ;
	while (com->argv)
	{
		com->argv[i] = word;
		i++;
	}
	i = 0;
	while (com->argv[i])
	{
		printf("Linea de envp: %s\n", com->argv[i]);
		i++;
	}
}

int	handle_pipe_token(char *input, t_optimize_data *optimize, int i)
{
	(void) input;
	add_token(&optimize->head, &optimize->current, TOKEN_PIPE, "|");
	return (i + 1);
}

int	handle_input_redir(char *input, t_optimize_data *optimize, int i)
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

int	handle_variable_token(char *input, t_optimize_data *optimize, int i, t_minishell *minishell)
{
	int		start;
	char	*str;
	char	*result;
	int		flag;

	flag = 0;
	start = i + 1;
	i++;
	while ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] == '_')
		|| (input[i] >= '0' && input[i] <= '9'))
	{
		flag = 1;
		i++;
	}
	if (flag == 1)
	{
		str = ft_substr(input, start, i - start);
		result = check_var_token(minishell, str);
		add_token(&optimize->head, &optimize->current, TOKEN_VAR, result);
		free(str);
		free(result);
		return (i);
	}
	else
	{
		add_token(&optimize->head, &optimize->current, TOKEN_WORD, "$");
		return (-1);
	}
}
