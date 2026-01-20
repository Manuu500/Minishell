/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:53:24 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/20 16:17:38 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
    char	*result;

	if (!s1 && !s2)
		return (NULL);
    if (!s2)
	{
		free(s2);
        return (s1);
	}
    if (!s1)
	{
        s1 = ft_strdup("");
		free(s2);
		return NULL;
	}
    result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (result);
}

int manage_dollar_case(t_optimize_data *opt, t_minishell *min, int i, int start)
{
	char *temp;

	if (i > start)
		opt->word = ft_strjoin_free(opt->word, ft_substr(opt->input, start, i - start));
	opt->var_value = include_legit_variable(opt->input, opt, i, min);
	if (opt->var_value)
	{
		temp = ft_strdup(opt->var_value);
		if (temp)
			opt->word = ft_strjoin_free(opt->word, temp);
	}
	i++;
	if (opt->input[i] == '?')
		return (i + 1);
	while (opt->input[i] && (ft_isalnum(opt->input[i]) || opt->input[i] == '_'))
		i++;
	return (i);
}

void join_strings(t_optimize_data *opt, int i, int start)
{
	if (i > start)
    {
        opt->word = ft_strjoin_free(opt->word, ft_substr(opt->input, start, i - start));
    }
}

int is_word(t_optimize_data *opt, int i)
{
    return (opt->input[i] != ' ' && opt->input[i] != '\t' 
        && opt->input[i] != '<' && opt->input[i] != '>' && opt->input[i] != '|');
}

int print_variable_content(t_optimize_data *opt, t_minishell *min, int i, int start)
{
	char *temp;

	join_strings(opt, i, start);
	opt->var_value = include_legit_variable(opt->input, opt, i, min);
	if (opt->var_value)
	{
		temp = ft_strdup(opt->var_value);
		if (temp)
			opt->word = ft_strjoin_free(opt->word, temp);
	}
	i++;
	while (opt->input[i] && opt->input[i] != opt->quote && (ft_isalnum(opt->input[i]) || opt->input[i] == '_'))
		i++;
	return (i);
}