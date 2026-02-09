/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:36:56 by mruiz-ur          #+#    #+#             */
/*   Updated: 2026/02/09 16:09:46 by mruiz-ur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

typedef struct minishell
{
	char	*user_input;
	char	**envp;
	int		run;
	int		last_exit_code;
	char	*del_word;
}			t_min;

typedef enum token_type
{
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

typedef struct s_redirect
{
	char				*filename;
	int					fd;
	struct s_redirect	*next;
	t_token_type		type;
}			t_redir;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*var_name;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

typedef struct s_optimize_data
{
	t_token		*head;
	t_redir		*head_red;
	t_token		*current;
	char		*word;
	char		*var_value;
	char		*input;
	char		quote;
	int			in_quote;
}				t_opt_data;

typedef struct s_command
{
	struct s_command	*next;
	t_redir				*redirs;
	char				**argv;
	int					in_fd;
	int					out_fd;
	int					redir_error;
	int					is_builtin;
}					t_command;

//---------------MATRIX_FUNCTIONS---------------//

char	**copy_matrix(char **envp);
void	free_matrix(char **matrix);

//----------------------------------------------//

void	init_vars(t_min *min, t_command *com, t_opt_data *opt);
void	safe_free(t_min *min, t_command *com, t_opt_data *opt, t_token *token);
t_token	*tokenize(char *input, t_min *minishell, t_opt_data *optimize);
void	debug_token(t_token *head);
void	check_if_pipes(char *input, int i, t_token *head, t_token *current);
int		check_if_number(char *input, int i, t_token *head, t_token *current);
void	add_token(t_token **head,
			t_token **current, t_token_type type, char *value);
void	syntax_check(t_command *command, t_token *tokens, t_redir *redirect);
void	save_command(t_command *command, t_min *minishell);
char	*find_var_in_matrix(char *var, t_min *minishell);
int		handle_pipe_token(char *input, t_opt_data *optimize, int i);
int		handle_input_redir(char *input, t_opt_data *optimize, int i);
int		handle_output_redir(char *input, t_opt_data *optimize, int i);
int		handle_variable_token(char *input,
			t_opt_data *optimize, int i, t_min *minishell);
int		handle_equal_redir(char *input, t_opt_data *optimize, int i);
char	*check_var_token(t_min *minishell, char *str);
char	*substr_remove_quotes(char *input, int start, int len, char quote_type);
int		process_word(char *input, int i,
			t_opt_data *optimize, t_min *minishell);
int		process_quotes(char	*input, int i, char quote);
void	add_word_to_com(char *word, t_command *com);
void	move_tokens_to_command(t_token *head, t_command *command, t_min *min);
void	tokens_to_command(t_token *tokens, t_command *com, t_min *min);
void	pipe_tokens_to_command(t_token *token, t_command *com, t_min *min);
void	save_filename_redirs(t_command *command, t_token *head);
size_t	word_count(char const *s, char c);
void	free_mem(char **str);
void	*include_legit_variable(char *input, t_opt_data *optimize,
			int i, t_min *minishell);
void	save_vars(t_min *minishell, t_token *token);
char	*ft_strjoin_free(char *s1, char *s2);
int		manage_dollar_case(t_opt_data *opt, t_min *min, int i, int start);
void	join_strings(t_opt_data *opt, int i, int start);
int		is_word(t_opt_data *opt, int i);
int		print_variable_content(t_opt_data *opt, t_min *min, int i, int start);
void	exit_program(t_min *ms, int err_snipet);
void	free_com_redirs(t_command *com);
void	free_com_argv(t_command *com);
int		next_is_word(t_token *current);
int		word_or_var(t_token *current);
int		is_redir(t_token *current);
void	err_token(t_command *com, t_min *min);
int		char_is_valid(char *input, int i);
void	join_word(t_opt_data *opt, int i, int start);

#endif