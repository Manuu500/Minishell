/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:56 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/10 17:28:50 by mruiz-ur         ###   ########.fr       */
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
	TOKEN_REDIR_IN, // <
	TOKEN_REDIR_OUT, // >
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_VAR
}			t_token_type;

typedef struct s_token {
	t_token_type 	type;
	char			*value;
	char			*var_name;
	struct s_token 	*next;
	struct s_token	*prev;
}			t_token;

typedef struct	s_redirect {
	char				*filename;
	int					fd;
	struct s_redirect 	*next;
	t_token_type		type;
}			t_redirect;

typedef struct s_command {
	char				**argv;
	// char				**input;
	t_redirect    		*redirs;  // lista enlazada de redirecciones para este comando
    int         		in_fd;      // init -1, ADRI lo rellena
    int         		out_fd;     // init -1
    int         		is_builtin; // init 0. Adri lo rellena
    struct s_command 	*next; // para pipeline
}			t_command;

//---------------MATRIX_FUNCTIONS---------------//

char	**copy_matrix(char **envp);
void	free_matrix(char **matrix);
void	debug_matrix_copy(t_minishell *minishell);

//----------------------------------------------//

void	init_vars(t_minishell *minishell, t_command *command, t_redirect *redirect);
void	safe_free(t_minishell *minishell, t_command *command);
t_token	*tokenize(char *input, t_minishell *minishell);
void	debug_token(t_token *head);
void	check_if_pipes(char *input, int i, t_token *head, t_token *current);
int		check_if_number(char *input, int i, t_token *head, t_token *current);
void	add_token(t_token **head, t_token **current, t_token_type type, char *value);
void	syntax_check(t_command *command, t_token *tokens, t_redirect *redirect);
void	save_command(t_command *command, t_minishell *minishell);
char	*find_var_in_matrix(char *var, t_minishell *minishell);

#endif