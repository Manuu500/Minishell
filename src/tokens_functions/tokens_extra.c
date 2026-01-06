/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:50:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/06 17:03:35 by mruiz-ur         ###   ########.fr       */
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

// int handle_equal_redir(char *input, t_optimize_data *optimize, int i)
// {
// 	(void) input;
// 	add_token(&optimize->head, &optimize->current, TOKEN_EQUAL, "=");
// 	return (i + 1);
// }

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
	int		flag;

	flag = 0;
    start = i + 1;
    i++;
    while (input[i] >= 'A' && input[i] <= 'Z')
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
		return (-1);
}

// int	process_word(char *input, int i, t_optimize_data *optimize, t_minishell *minishell)
// {
// 	int		start;
// 	char	*temp;
// 	char	*word;
// 	char	*test_word;
// 	char	quote;
// 	int		inside_quotes;
	
// 	start = i;
// 	while (input[i])
// 	{
// 		inside_quotes = 0;
// 		if (input[i] == '\'' || input[i] == '\"')
// 		{
// 			inside_quotes = 1;
// 			quote = input[i];
// 			i = process_quotes(input, i, quote);
// 		}
// 		else if (input[i] == '$')
//         {
//             test_word = include_legit_variable(input, optimize, i, minishell);
//             word = ft_strjoin(word, test_word);
// 			i++;
//         }
// 		else if (inside_quotes == 0 && (input[i] == ' ' || input[i] == '\t' || input[i] == '<'
// 			|| input[i] == '>' || input[i] == '|'))
// 			break;
// 		else
// 			i++;
// 	}
// 	word = ft_strjoin(word, temp);
// 	add_token(&optimize->head, &optimize->current, TOKEN_WORD, word);
//     free(word);
// 	return (i);
// }
		// add_word_to_com(word, com);
