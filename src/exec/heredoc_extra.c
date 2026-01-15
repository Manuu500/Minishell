/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:37:37 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/15 12:39:19 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_if_alpha(char *line, int i)
{
    while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
        i++;
    return (i);
}

static char *get_var_value(char *line, int *i, t_minishell *ms)
{
    char    *var_name;
    char    *var_value;
    int     start;

    start = ++(*i);
    *i = check_if_alpha(line, *i);
    var_name = ft_substr(line, start, *i - start);
    var_value = check_var_token(ms, var_name);
    free(var_name);
    if (!var_value)
        var_value = ft_strdup("");
    return (var_value);
}

static char *append_str(char *result, char *to_add)
{
    char    *temp;

    temp = ft_strjoin(result, to_add);
    free(result);
    free(to_add);
    return (temp);
}

char *expand_variables(char *line, t_minishell *ms)
{
    char    *result;
    char    *temp;
    int     i;
    
    result = ft_strdup("");
    i = 0;
    while (line[i])
    {
        if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'))
            result = append_str(result, get_var_value(line, &i, ms));
        else
        {
            temp = ft_substr(line, i++, 1);
            result = append_str(result, temp);
        }
    }
    return (result);
}