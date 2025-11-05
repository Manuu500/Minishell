NAME	:= minishell

CC = cc

CFLAGS	:= -Wextra -Wall -Werror -g -Isrc

LIBFT := ./libs/libft

HEADERS	:=	-I ./inc \
			-I $(LIBFT)

LIBS := $(LIBFT)/libft.a

SRC :=	src/main.c \
		src/utils.c \
		src/free.c \
<<<<<<< HEAD
	src/debug.c \
	src/syntax.c \
	src/tokens_functions/tokens.c \
	src/tokens_functions/tokens_extra.c \
=======
		src/debug.c \
		src/syntax.c \
		src/tokens_functions/tokens.c \
		src/tokens_functions/tokens_extra.c \
>>>>>>> origin/parse_branch
		src/matrix_utils/copy_matrix.c \
		src/matrix_utils/free_matrix.c \
	src/builtings/builtings.c \
	src/builtings/echo.c \
	src/builtings/env.c \
	src/builtings/pwd.c \
	src/builtings/cd.c \
	src/builtings/export.c \
	src/builtings/unset.c \
	src/builtings/exit.c \
		src/exec/command_dispatcher.c \
		src/exec/exe_utils.c \
		src/exec/exe_runner.c \
		src/exec/argv_builder.c

OBJ	= $(patsubst src%, obj%, $(SRC:.c=.o))

all: libft obj $(NAME)

libft:
	@make -C $(LIBFT) all

$(NAME): $(OBJ)
	@echo "compiling ${NAME}"
	@$(CC) $(CFLAGS) $(OBJ) $(HEADERS) -o $(NAME) $(LIBS) -lreadline

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

obj/%.o: bonus/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

obj:
	@mkdir -p obj
	@mkdir -p obj/matrix_utils
<<<<<<< HEAD
	@mkdir -p obj/tokens_functions
=======
	@mkdir -p obj/tokens_functions
>>>>>>> origin/parse_branch

clean:
	@rm -rf obj
	@make -C libs/libft clean
# 	@mkdir -p obj/matrix_utils

fclean: clean
	@make -C libs/libft fclean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libft, obj