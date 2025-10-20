NAME	:= minishell

CC = cc

CFLAGS	:= -Wextra -Wall -Werror -g

HEADERS	:=	-I ./inc 

SRC :=	src/main.c \

OBJ	= $(patsubst src%, obj%, $(SRC:.c=.o))

all: obj $(NAME)

libft:
	@make -C libs/libft all

$(NAME): $(OBJ)
	@echo "compiling ${NAME}"
	@$(CC) $(CFLAGS) $(OBJ) $(HEADERS) -o $(NAME) -lreadline

obj/%.o: src/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

obj/%.o: bonus/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

obj:
	@mkdir -p obj

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft, obj