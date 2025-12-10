/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:21:00 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/12/10 13:11:16 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*ft_strjoin_free(char *s1, char *s2)
{
    char	*result;

	if (!s1 || !s2)
		return (s1);
    result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (result);
}

static	int manage_dollar_case(t_optimize_data *opt, t_minishell *min, int i, int start)
{
	if (i > start)
		opt->word = ft_strjoin_free(opt->word, ft_substr(opt->input, start, i - start));
	opt->var_value = include_legit_variable(opt->input, opt, i, min);
	if (opt->var_value)
		opt->word = ft_strjoin_free(opt->word, opt->var_value);
	i++;
	while (opt->input[i] && (ft_isalnum(opt->input[i]) || opt->input[i] == '_'))
		i++;
	return (i);
}

static	void join_strings(t_optimize_data *opt, int i, int start)
{
	if (i > start)
        opt->word = ft_strjoin_free(opt->word, ft_substr(opt->input, start, i - start));
}

static  int not_word(t_optimize_data *opt, int i)
{
    return (opt->input[i] != ' ' && opt->input[i] != '\t' 
        && opt->input[i] != '<' && opt->input[i] != '>' && opt->input[i] != '|');
}

static  int print_variable_content(t_optimize_data *opt, t_minishell *min, int i, int start)
{
	join_strings(opt, i, start);
	opt->var_value = include_legit_variable(opt->input, opt, i, min);
	if (opt->var_value)
		opt->word = ft_strjoin_free(opt->word, opt->var_value);
	i++;
	while (opt->input[i] && opt->input[i] != opt->quote && (ft_isalnum(opt->input[i]) || opt->input[i] == '_'))
		i++;
	return (i);
}

int	process_word(char *input, int i, t_optimize_data *optimize, t_minishell *minishell)
{
    int			start;
    
	optimize->input = input;
    optimize->word = ft_strdup("");
    start = i;
    while (optimize->input[i] && not_word(optimize, i))
    {
        if (input[i] == '\'' || input[i] == '\"')
        {
			join_strings(optimize, i, start);
            optimize->quote = input[i];
            i++;
            start = i;
            while (input[i] && input[i] != optimize->quote)
            {
                if (input[i] == '$' && optimize->quote == '\"')
                {
                    i = print_variable_content(optimize, minishell, i, start);
                    start = i;
                }
                else
                    i++;
            }
            join_strings(optimize, i, start);
            i++;
            start = i;
        }
        else if (input[i] == '$')
        {
			i = manage_dollar_case(optimize, minishell, i, start);
            start = i;
        }
		else
            i++;
    }
    join_strings(optimize, i, start);
    add_token(&optimize->head, &optimize->current, TOKEN_WORD, optimize->word);
    free(optimize->word);
    return (i);
}
