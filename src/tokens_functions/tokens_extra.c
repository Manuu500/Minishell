/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:50:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/02 12:32:35 by mruiz-ur         ###   ########.fr       */
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

int	handle_pipe_token(char *input, t_opt_data *optimize, int i)
{
	(void) input;
	add_token(&optimize->head, &optimize->current, TOKEN_PIPE, "|");
	return (i + 1);
}

int	handle_input_redir(char *input, t_opt_data *optimize, int i)
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

int	handle_output_redir(char *input, t_opt_data *optimize, int i)
{
	if (input[i + 1] == '>')
	{
		add_token(&optimize->head, &optimize->current,
			TOKEN_REDIR_APPEND, ">>");
		return (i + 2);
	}
	else
	{
		add_token(&optimize->head, &optimize->current, TOKEN_REDIR_OUT, ">");
		return (i + 1);
	}
}

int	handle_variable_token(char *input, t_opt_data *opt, int i, t_min *min)
{
	int		start;
	char	*str;
	char	*result;

	start = i + 1;
	i++;
	while (char_is_valid(input, i))
		i++;
	if (i > start)
	{
		str = ft_substr(input, start, i - start);
		result = check_var_token(min, str);
		add_token(&opt->head, &opt->current, TOKEN_VAR, result);
		free(str);
		free(result);
		return (i);
	}
	add_token(&opt->head, &opt->current, TOKEN_WORD, "$");
	return (-1);
}
