/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:56 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/01/13 13:16:01 by mruiz-ur         ###   ########.fr       */
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
	int		run;
	int		last_exit_code;
}			t_minishell;

typedef enum token_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN, // <
	TOKEN_REDIR_OUT, // >
	TOKEN_EQUAL, // =
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_COMMAND,
	TOKEN_VAR
}			t_token_type;

typedef struct	s_redirect {
	char				*filename;
	int					fd;
	struct s_redirect 	*next;
	t_token_type		type;
}			t_redirect;

typedef struct s_token {
	t_token_type 	type;
	char			*value;
	char			*var_name;
	struct s_token 	*next;
	struct s_token	*prev;
}			t_token;

typedef struct	s_optimize_data {
	t_token		*head;
	t_redirect	*head_red;
	t_token		*current;
	char		*word;
	char		*var_value;
	char		*input;
	char		quote;
	int			in_quote;
}				t_optimize_data;

typedef struct s_command {
	char				**argv;
	// char				**input;
	t_redirect    		*redirs;  // lista enlazada de redirecciones para este comando
    int         		in_fd;      // init -1. ADRI lo rellena
    int         		out_fd;     // init -1
	int					redir_error; // set 1 if error and end the command.
    int         		is_builtin; // init 0. Adri lo rellena
    struct s_command 	*next; // para pipeline
}			t_command;

//---------------MATRIX_FUNCTIONS---------------//

char	**copy_matrix(char **envp);
void	free_matrix(char **matrix);

//----------------------------------------------//

void	init_vars(t_minishell *minishell, t_command *command, t_optimize_data *optimize);
void	safe_free(t_minishell *minishell, t_command *command, t_optimize_data *opt, t_token *token);
t_token	*tokenize(char *input, t_minishell *minishell, t_optimize_data *optimize);
void	debug_token(t_token *head);
void	check_if_pipes(char *input, int i, t_token *head, t_token *current);
int		check_if_number(char *input, int i, t_token *head, t_token *current);
void	add_token(t_token **head, t_token **current, t_token_type type, char *value);
void	syntax_check(t_command *command, t_token *tokens, t_redirect *redirect);
void	save_command(t_command *command, t_minishell *minishell);
char	*find_var_in_matrix(char *var, t_minishell *minishell);
int		handle_pipe_token(char *input, t_optimize_data *optimize, int i);
int 	handle_input_redir(char *input, t_optimize_data *optimize, int i);
int		handle_output_redir(char *input, t_optimize_data *optimize, int i);
int 	handle_variable_token(char *input, t_optimize_data *optimize, int i, t_minishell *minishell);
int 	handle_equal_redir(char *input, t_optimize_data *optimize, int i);
char	*check_var_token(t_minishell *minishell, char *str);
char	*substr_remove_quotes(char *input, int start, int len, char quote_type);
int		process_word(char *input, int i, t_optimize_data *optimize, t_minishell *minishell);
int		process_quotes(char	*input, int i, char quote);
void	add_word_to_com(char *word, t_command *com);
void	move_tokens_to_command(t_token *head, t_command *command, t_minishell *min);
void	tokens_to_command(t_token *tokens, t_command *com, t_minishell *min);
void	pipe_tokens_to_command(t_token *token, t_command *com, t_minishell *min);
void	save_filename_redirs(t_command *command, t_token *head);
size_t	word_count(char const *s, char c);
void	free_mem(char **str);
void	*include_legit_variable(char *input, t_optimize_data *optimize, int i, t_minishell *minishell);
void	save_vars(t_minishell *minishell, t_token *token);
char	*ft_strjoin_free(char *s1, char *s2);
int 	manage_dollar_case(t_optimize_data *opt, t_minishell *min, int i, int start);
void 	join_strings(t_optimize_data *opt, int i, int start);
int 	is_word(t_optimize_data *opt, int i);
int 	print_variable_content(t_optimize_data *opt, t_minishell *min, int i, int start);
void	exit_program(t_minishell *ms, int err_snipet);

#endif