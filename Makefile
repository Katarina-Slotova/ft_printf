# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: katarinka <katarinka@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 13:55:36 by kslotova          #+#    #+#              #
#    Updated: 2022/02/07 11:09:05 by katarinka        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf

SOURCES = ft_printf.c main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc -Wall -Wextra -Werror -c $(SOURCES)
	gcc -o $(NAME) $(OBJECTS) -L./libft -lft

clean:
	/bin/rm -f $(OBJECTS)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
