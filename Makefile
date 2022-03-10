# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 11:42:56 by bbordere          #+#    #+#              #
#    Updated: 2022/03/10 11:51:39 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = ./

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES) -O3

SCRS = main.c

OBJS = $(SCRS:.c=.o)

NAME = philo

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

all: $(NAME)

debug:
	$(CC) $(CFLAGS) -g3 $(OBJS) -lpthread -o $(NAME)

debug_thread:
	$(CC) $(CFLAGS) -g3 -fsanitize=thread $(OBJS) -lpthread -o $(NAME)

clean:
	@ rm -f $(OBJS)

fclean : clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(OBJS)