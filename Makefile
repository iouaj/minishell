NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = minishell.h

FILES =	minishell \
		utils \
		parsing \
		builtins \
		env

SRC = $(addsuffix .c, $(FILES))

OBJ = $(SRC:.c=.o)

LIBFT = libft

all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDES) $(LIBFT)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a -lreadline -I $(INCLUDES) -o $(NAME)

clean:
	make fclean -C $(LIBFT)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
