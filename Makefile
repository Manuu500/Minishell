NAME	:= minishell

CC = cc

CFLAGS	:= -Wextra -Wall -Werror -g -Isrc

LIBFT := ./libs/libft

HEADERS	:=	-I ./inc \
			-I $(LIBFT)

LIBS := $(LIBFT)/libft.a

SRC :=	src/main.c \
		src/utils.c \
		src/matrix_utils/copy_matrix.c \
		src/matrix_utils/free_matrix.c

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

clean:
	@rm -rf obj
	@make -C libs/libft clean
# 	@mkdir -p obj/matrix_utils

fclean: clean
	@make -C libs/libft fclean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libft, obj