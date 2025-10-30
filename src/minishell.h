/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arivas-q <arivas-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:56 by mruiz-ur          #+#    #+#             */
/*   Updated: 2025/10/30 16:30:54 by arivas-q         ###   ########.fr       */
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
}			t_token;

//---------------MATRIX_FUNCTIONS---------------//

char	**copy_matrix(char **envp);
void	free_matrix(char **matrix);
void	debug_matrix_copy(t_minishell *minishell);

//----------------------------------------------//

void	init_vars(t_minishell *minishell);
void	safe_free(t_minishell *minishell);
t_token	*tokenize(char *input);
void	debug_token(t_token *head);
void	check_if_pipes(char *input, int i, t_token *head, t_token *current);
int		check_if_number(char *input, int i, t_token *head, t_token *current);
void	add_token(t_token **head, t_token **current, t_token_type type, char *value);

#endif