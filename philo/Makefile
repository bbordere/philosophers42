# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 11:42:56 by bbordere          #+#    #+#              #
#    Updated: 2022/08/22 00:15:29 by bbordere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = ./includes

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES)

SCRS = main.c init.c routine.c monitor.c time.c exit.c utils.c parsing.c forks.c utils_routine.c

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

