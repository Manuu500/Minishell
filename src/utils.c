/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:49:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/16 11:00:32 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_min *min, t_command *com, t_opt_data *opt)
{
	ft_bzero(com, sizeof(t_command));
	ft_bzero(opt, sizeof(t_opt_data));
	com->redirs = malloc(sizeof(t_redir));
	if (!com->redirs)
		return ;
	min->user_input = NULL;
	opt->head_red = NULL;
	opt->current = NULL;
	opt->head = NULL;
	opt->input = NULL;
	opt->var_value = NULL;
	opt->word = NULL;
	opt->quote = 0;
	opt->in_quote = 0;
	com->redirs->fd = -1;
	com->redirs->filename = NULL;
	com->redirs->next = NULL;
	com->redirs->type = 0;
	com->argv = NULL;
	com->in_fd = STDIN_FILENO;
	com->out_fd = STDOUT_FILENO;
	com->redir_error = 0;
	com->next = NULL;
}

static	int	word_is_argument(t_token *current)
{
	return ((current->prev && (current->prev->type == TOKEN_REDIR_IN
				|| current->prev->type == TOKEN_REDIR_OUT
				|| current->prev->type == TOKEN_REDIR_APPEND
				|| current->prev->type == TOKEN_HEREDOC)));
}

static void	add_to_argv(t_command *command, t_token *current, int *i)
{
	command->argv[*i] = ft_strdup(current->value);
	if (!command->argv[*i])
	{
		free_mem(command->argv);
		return ;
	}
	(*i)++;
	command->argv[*i] = NULL;
}

static void	initialize_argv(t_command *command, int j, int num_words)
{
	while (j <= num_words)
	{
		command->argv[j] = NULL;
		j++;
	}
}

void	move_tokens_to_command(t_token *head, t_command *command, t_min *min)
{
	t_token	*current;
	int		i_argv;
	int		num_words;
	int		j;

	i_argv = 0;
	current = head;
	num_words = word_count(min->user_input, ' ');
	command->argv = malloc((sizeof(char *)) * (num_words + 1));
	if (!command->argv)
		return ;
	j = 0;
	initialize_argv(command, j, num_words);
	while (current)
	{
		if ((word_or_var(current))
			&& (!word_is_argument(current) || !current->prev))
			add_to_argv(command, current, &i_argv);
		if (is_redir(current) && !next_is_word(current))
			return (err_token(command, min));
		current = current->next;
	}
	save_filename_redirs(command, head);
}

// printf("=== COMANDOS EN ARGV ===\n");
//     if (command->argv)
//     {
//         while (command->argv[i])
//         {
//             printf("argv[%d]: %s\n", i, command->argv[i]);
//             i++;
//         }
//         printf("Total comandos: %d\n", i);
//     }
//     else
//     {
//         printf("argv es NULL\n");
//     }
//     printf("=======================\n");

// Para cada token:
//   Si es el primer TOKEN_WORD → COMANDO
//   Si es TOKEN_WORD y el token anterior es redirección → ARCHIVO
//   Si es TOKEN_WORD en cualquier otro caso → ARGUMENTO
//   Si es TOKEN_REDIR_* → OPERADOR DE REDIRECCIÓN
