NAME	:= minishell

CC = cc

CFLAGS	:= -Wextra -Wall -Werror -g -Isrc

LIBFT := ./libs/libft

HEADERS	:= -I $(LIBFT)

LIBS := $(LIBFT)/libft.a

SRC :=	src/main.c \
	src/utils.c \
	src/free.c \
	src/syntax.c \
	src/variable.c \
	src/utils_extra.c \
	src/utils_extra_extra.c \
	src/tokens_functions/tokens.c \
	src/tokens_functions/tokens_extra.c \
	src/tokens_functions/tokens_extra_extra.c \
	src/tokens_functions/tokens_proc_word.c \
	src/tokens_functions/process_word_extra.c \
	src/tokens_functions/process_word.c \
	src/matrix_utils/copy_matrix.c \
	src/matrix_utils/free_matrix.c \
	src/matrix_utils/find_matrix.c \
	src/exec/command_dispatcher.c \
	src/exec/exe_runner.c \
	src/exec/exe_utils.c \
	src/exec/pipes.c \
	src/exec/pipe_loop.c \
	src/exec/pipes_utils.c \
	src/exec/redirs.c \
	src/exec/heredoc.c \
	src/exec/heredoc_extra.c \
	src/builtings/builtings.c \
	src/builtings/cd.c \
	src/builtings/echo.c \
	src/builtings/env.c \
	src/builtings/exit.c \
	src/builtings/export.c \
	src/builtings/pwd.c \
	src/builtings/unset.c \
	src/signals/Ctrl_Sig.c \
	src/signals/signal.c

OBJ	:= $(patsubst src%, obj%, $(SRC:.c=.o))

all: libft obj $(NAME)

libft:
	@make -C $(LIBFT) all

$(NAME): $(OBJ)
	@echo "compiling ${NAME}"
	# Generar el ejecutable en el mismo directorio que este Makefile
	@$(CC) $(CFLAGS) $(OBJ) $(HEADERS) -o $(CURDIR)/$(NAME) $(LIBS) -lreadline -lncurses

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

obj:
	@mkdir -p obj
	@mkdir -p obj/matrix_utils
	@mkdir -p obj/tokens_functions
	@mkdir -p obj/builtings
	@mkdir -p obj/exec
	@mkdir -p obj/signals

clean:
	@rm -rf obj
	@make -C libs/libft clean

fclean: clean
	@make -C libs/libft fclean
	@rm -f $(CURDIR)/$(NAME)

re: clean all

.PHONY: all clean fclean re libft obj