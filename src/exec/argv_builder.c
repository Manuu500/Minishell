/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:25:41 by arivas-q          #+#    #+#             */
/*   Updated: 2025/11/03 10:18:32 by arivas-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

size_t	argv_word_count(t_token *token)
{
	size_t		count;
	t_token		*cur;

	count = 0;
	cur = token;
	while (cur && cur->type == TOKEN_WORD)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char	**argv_from_tokens(t_token *token, size_t count)
{
	char	**argv;
	size_t	i;
	t_token	*cur;

	i = 0;
	cur = token;
	if (count == 0)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	while (cur && cur->type == TOKEN_WORD && i < count)
	{
		argv[i++] = cur->value;
		cur = cur->next;
	}
	argv[i] = NULL;
	return (argv);
}

char	**make_argv_view_from_tokens(t_token *token)
{
	size_t	count;

	count = argv_word_count(token);
	if (count == 0)
		return (NULL);
	return (argv_from_tokens(token, count));
}
