# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huaydin <huaydin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 10:08:30 by huaydin           #+#    #+#              #
#    Updated: 2023/02/06 16:06:55 by huaydin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_NAME =	main.c eat_sleep_think.c routine.c utils.c thread_init.c

SRCS = $(addprefix src/,$(SRCS_NAME))

OBJ = $(addprefix obj/,$(SRCS_NAME:.c=.o))

CC = cc

CFLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(CFLAGS) -o $(NAME) -lpthread

obj/%.o:src/%.c
		@mkdir -p obj
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ) obj

fclean: clean
		rm -rf $(NAME)

re: fclean all
