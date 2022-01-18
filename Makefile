# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 11:19:39 by cbignon           #+#    #+#              #
#    Updated: 2022/01/18 11:42:11 by cbignon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	main.c \
		clean.c \
		god_ft.c \
		init.c \
		philo_actions.c \
		thread.c \
		print.c \
		utils.c \
		check.c \
		time.c \
		forks.c \
		
OBJ = $(SRC:.c=.o)

CC = clang
FLAGS = -Wall -Werror -Wextra

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
