# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 11:19:39 by cbignon           #+#    #+#              #
#    Updated: 2022/01/13 14:43:37 by cbignon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	clean.c \
		god_ft.c \
		init.c \
		main.c \
		philo_actions.c \
		thread.c \
		print.c \
		utils.c \
		check.c \
		time.c \
		forks.c \
		
OBJ = $(SRC:.c=.o)

CC = clang
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread

LIB = -lpthread

all:	$(NAME)
	@echo "philo is ready!"

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

.c.o:
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@
	
clean: 
	@rm -rf $(OBJ)
	@echo "clean *.o"

fclean:	clean
	@rm -rf $(NAME)
	@echo "everything is clean!"

re: fclean all
