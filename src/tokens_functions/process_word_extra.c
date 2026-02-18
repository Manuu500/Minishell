/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:53:24 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/18 13:38:44 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

int	manage_dollar_case(t_opt_data *opt, t_min *min, int i, int start)
{
	if (i > start)
		opt->word = ft_strjoin_free(opt->word,
				ft_substr(opt->input, start, i - start));
	opt->var_value = include_legit_variable(opt->input, opt, i, min);
	if (opt->var_value)
		opt->word = ft_strjoin_free(opt->word, opt->var_value);
	opt->var_value = NULL;
	i++;
	if (opt->input[i] == '?')
		return (i + 1);
	while (opt->input[i] && (ft_isalnum(opt->input[i]) || opt->input[i] == '_'))
		i++;
	return (i);
}

void	join_strings(t_opt_data *opt, int i, int start)
{
	if (i > start)
	{
		opt->word = ft_strjoin_free(opt->word,
				ft_substr(opt->input, start, i - start));
	}
}

int	is_word(t_opt_data *opt, int i)
{
	return (opt->input[i] != ' ' && opt->input[i] != '\t'
		&& opt->input[i] != '<' && opt->input[i]
		!= '>' && opt->input[i] != '|');
}

int	print_variable_content(t_opt_data *opt, t_min *min, int i, int start)
{
	join_strings(opt, i, start);
	opt->var_value = include_legit_variable(opt->input, opt, i, min);
	if (opt->var_value)
		opt->word = ft_strjoin_free(opt->word, opt->var_value);
	opt->var_value = NULL;
	i++;
	if (opt->input[i] == '?')
		return (i + 1);
	while (opt->input[i] && opt->input[i] != opt->quote
		&& (ft_isalnum(opt->input[i]) || opt->input[i] == '_'))
		i++;
	return (i);
}
