/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:49:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/12/12 21:44:50 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	init_vars(t_minishell *minishell, t_command *command, t_redirect *redirect, t_optimize_data *optimize)
{
	(void)	redirect;
	(void)	command;
	
	command->redirs = malloc(sizeof(t_redirect));
    if (!command->redirs)
	{
        return;
	}
	minishell->envp = NULL;
	minishell->user_input = NULL;
	// 12/10/2025, Último cambio, cambiar "head" por "optimize->head"
	optimize->head_red = malloc(sizeof(t_redirect));
	if (!optimize->head_red)
		return ;
	command->redirs->fd = -1;
	command->redirs->filename = NULL;
	command->redirs->next = NULL;
	command->redirs->type = 0;
	// redirect->fd = -1;
	// redirect->filename = NULL;
	// redirect->next = NULL;
	// redirect->type = 0;
	command->in_fd = STDIN_FILENO;
	command->out_fd = STDOUT_FILENO;
	command->redir_error = 0;
	command->next = NULL;
	optimize->head = NULL;
    optimize->current = NULL;
}

static	int	word_is_argument(t_token *current)
{
	return ((current->prev && (current->prev->type == TOKEN_REDIR_IN
			|| current->prev->type == TOKEN_REDIR_OUT
			|| current->prev->type == TOKEN_REDIR_APPEND
			|| current->prev->type == TOKEN_HEREDOC)));
}

static void	initialize_argv(t_command *command, int j, int num_words)
{
	while (j <= num_words)
	{
		command->argv[j] = NULL;
		j++;
	}
}

static  void    add_to_argv(t_command *command, t_token *current, int *i)
{
	command->argv[*i] = ft_strdup(current->value);
    if (!command->argv[*i])
    {
        free_mem(command->argv);
        return;
    }
    (*i)++;
    command->argv[*i] = NULL; 
}

int	check_tokens(t_token *token)
{	
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void	tokens_to_command(t_token *tokens, t_command *com, t_minishell *min)
{
	int	is_pipe;
	
	is_pipe = check_tokens(tokens);
	if (is_pipe)
		pipe_tokens_to_command(tokens, com, min);
	else
		move_tokens_to_command(tokens, com, min);
}

void	pipe_tokens_to_command(t_token *token, t_command *com, t_minishell *min)
{
	t_token *split;
	t_token *next_split;

	(void) min;
	(void) com;
	(void) next_split;
	split = token;
	next_split = NULL;
	if (!token)
		return ;
	while (split && split->type != TOKEN_PIPE)
		split = split->next;
	if (split)
		printf("He llegado al pipe");
}

void	move_tokens_to_command(t_token *head, t_command *command, t_minishell *min)
{
	t_token *current;
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
		if (current->type == TOKEN_WORD || current->type == TOKEN_VAR)
        {
            if (!(word_is_argument(current)))
                add_to_argv(command, current, &i_argv);
			else if (current && !(current->prev))
				add_to_argv(command, current, &i_argv);
        }
        current = current->next;
    }
	// int	i = 0;
	// printf("=== COMANDOS EN ARGV ===\n");
    // if (command->argv)
    // {
    //     while (command->argv[i])
    //     {
    //         printf("argv[%d]: %s\n", i, command->argv[i]);
    //         i++;
    //     }
    //     printf("Total comandos: %d\n", i);
    // }
    // else
    // {
    //     printf("argv es NULL\n");
    // }
    // printf("=======================\n");
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
