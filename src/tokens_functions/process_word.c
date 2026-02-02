/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:21:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/02 12:32:07 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_opt_data *opt, char *input)
{
	opt->input = input;
	opt->word = ft_strdup("");
	opt->in_quote = 0;
}

static int	init_data_quote(t_opt_data *opt, int i, int *start)
{
	join_strings(opt, i, *start);
	opt->quote = opt->input[i];
	i++;
	*start = i;
	return (i);
}

static int	manage_dollar_quote_case(t_opt_data *opt, t_min *min,
		int i, int *start)
{
	if (opt->input[i] == '$' && opt->quote == '\"')
	{
		i = print_variable_content(opt, min, i, *start);
		*start = i;
	}
	else
		i++;
	return (i);
}

static int	manage_lone_quote_case(t_opt_data *opt,
		t_min *min, int i, int start)
{
	i = init_data_quote(opt, i, &start);
	while (opt->input[i])
	{
		if (opt->input[i] != opt->quote)
		{
			opt->in_quote = 1;
			i = manage_dollar_quote_case(opt, min, i, &start);
		}
		else
		{
			join_strings(opt, i, start);
			opt->in_quote = 0;
			i++;
			return (i);
		}
	}
	printf("Error: unclosed quote");
	opt->in_quote = 0;
	return (-1);
}

int	process_word(char *input, int i, t_opt_data *opt, t_min *min)
{
	int	start;

	init_data(opt, input);
	start = i;
	while (opt->input[i] && opt->input[i + 1] != '|')
	{
		if (opt->in_quote == 0 && (!is_word(opt, i)))
			break ;
		if (opt->input[i] == '\'' || opt->input[i] == '\"')
		{
			i = manage_lone_quote_case(opt, min, i, start);
			if (i < 0)
				return (i);
			start = i;
		}
		else if (input[i] == '$')
		{
			i = manage_dollar_case(opt, min, i, start);
			start = i;
		}
		else
			i++;
	}
	join_strings(opt, i, start);
	add_token(&opt->head, &opt->current, TOKEN_WORD, opt->word);
	free(opt->word);
	return (i);
}
