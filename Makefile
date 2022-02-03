# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 13:55:36 by kslotova          #+#    #+#              #
#    Updated: 2022/02/03 18:03:38 by katarinka        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf

SOURCES = printf.c ft_strcharjoin.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -Wall -Wextra -Werror -c $(SOURCES)
	gcc -o $(NAME) $(OBJECTS) -L./libft -libft

clean:
	/bin/rm -f $(OBJECTS)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
