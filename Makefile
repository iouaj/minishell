NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = minishell.h

FILES =	minishell \
		ft_strncmp \
		ft_strlen \
		ft_strtrim \
		ft_split \
		utils \
		parsing

SRC = $(addsuffix .c, $(FILES))

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -I $(INCLUDES) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
