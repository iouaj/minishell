NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES =	minishell \
		ft_strncmp \
		ft_strlen

SRC = $(addsuffix .c, $(FILES))

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
