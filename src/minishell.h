/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:56 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/05 12:18:23 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

typedef struct minishell {
	char 	*user_input;
	char	**envp;
}			t_minishell;

typedef enum token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF	
}			t_token_type;

typedef struct s_token {
	t_token_type 	type;
	char			*value;
	struct s_token 	*next;
	struct s_token	*prev;
}			t_token;

typedef struct	s_redirect {
	char			**value;
	t_token_type	type;
}			t_redirect;

typedef struct s_command {
	char	**arg;
	char	**input;
}			t_command;

//---------------MATRIX_FUNCTIONS---------------//

char	**copy_matrix(char **envp);
void	free_matrix(char **matrix);
void	debug_matrix_copy(t_minishell *minishell);

//----------------------------------------------//

void	init_vars(t_minishell *minishell, t_command *command, t_redirect *redirect);
void	safe_free(t_minishell *minishell, t_command *command);
t_token	*tokenize(char *input);
void	debug_token(t_token *head);
void	check_if_pipes(char *input, int i, t_token *head, t_token *current);
int		check_if_number(char *input, int i, t_token *head, t_token *current);
void	add_token(t_token **head, t_token **current, t_token_type type, char *value);
void	syntax_check(t_command *command, t_token *tokens, t_redirect *redirect);

#endif