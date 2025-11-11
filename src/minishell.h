/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:56 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/11/06 12:27:47 by arivas-q         ###   ########.fr       */
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
	t_token *token;
}			t_command;

/*

typedef enum e_redir_type {
    REDIR_IN,
    REDIR_OUT,
    REDIR_OUT_APPEND,
    REDIR_HEREDOC								<---|
} t_redir_type;										|
													|
typedef struct s_redir {							|
    t_redir_type    type;		// tipo de redir (arriba)
    char            *filename;  // nombre
    int             fd;         // -1 hasta que se abra
    struct s_redir  *next;		// próxima redirección en la lista
} t_redir;

typedef struct s_command {
    char        **argv;     // matriz con todo el comando. Separar por pipe argv[0] = comando;
    int         argc;       // (no se si esto sirve para algo)
    t_redir     *redirs;    // lista enlazada de redirecciones para este comando
    int         in_fd;      // init -1, ADRI lo rellena
    int         out_fd;     // init -1
    int         is_builtin; // init 0. Adri lo rellena
    struct s_command *next; // para pipeline
} t_command;

*/

//---------------MATRIX_FUNCTIONS---------------//

char	**copy_matrix(char **envp);
void	free_matrix(char **matrix);

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