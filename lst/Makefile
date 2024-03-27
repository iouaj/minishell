NAME = test_lst

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = mini.h

FILES =	main \
		builtins

SRC = $(addsuffix .c, $(FILES))

OBJ = $(SRC:.c=.o)

LIBFT = libft

RED =\033[1;31m
GREEN =\033[1;32m
CYAN =\033[1;36m
COLOR_OFF =\033[0m

BIGREEN=\033[1;92m

%.o : %.c
	@$(CC) $(CFLAGS) -c $^

all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDES) $(LIBFT)
	@make bonus -C $(LIBFT) --no-print-directory
	@echo "$(GREEN)Libft create.$(COLOR_OFF)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a -lreadline -I $(INCLUDES) -o $(NAME)
	@echo "$(BIGREEN)Minishell create.$(COLOR_OFF)"

clean:
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -f $(OBJ)
	@echo "$(CYAN)Minishell cleaned.$(COLOR_OFF)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Minishell destroy.$(COLOR_OFF)"

re: fclean
	@make all --no-print-directory

.PHONY: all clean fclean re
