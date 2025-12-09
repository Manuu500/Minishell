/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:49:09 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/12/09 18:56:44 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	init_vars(t_minishell *minishell, t_command *command, t_redirect *redirect, t_optimize_data *optimize)
{
	(void)	command;
	t_redirect *head;

	command->redirs = redirect;
	minishell->envp = NULL;
	minishell->user_input = NULL;
	head = malloc(sizeof(t_redirect));
	if (!head)
		return ;
	redirect->fd = -1;
	redirect->filename = NULL;
	redirect->next = NULL;
	redirect->type = 0;
	command->in_fd = STDIN_FILENO;
	command->out_fd = STDOUT_FILENO;
	command->redir_error = 0;
	command->next = NULL;
	// command->redirs = malloc(sizeof(t_command));
	// command->argv = malloc(sizeof(char) * 200);
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
