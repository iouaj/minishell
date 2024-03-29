# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 21:52:24 by  souaguen         #+#    #+#              #
#    Updated: 2024/03/29 16:44:55 by iouajjou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-g -I./libft -I./#-Wall -Wextra -Werror
SRC= main.c \
    src/ft_strtok.c \
    src/ft_parsing.c \
    src/ft_env_parsing.c \
	main2.c \
	env.c \
	builtins.c \
	pipe.c \
	utils.c

NAME=minishell
OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	make -C libft all bonus
	$(CC) -g $(OBJ) -o $(NAME) -L./libft -l:libft.a -lreadline

all: $(NAME)

norme:
	norminette $(SRC)

clean:
	rm -f $(OBJ) $(BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
