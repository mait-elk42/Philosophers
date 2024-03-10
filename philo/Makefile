# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 10:25:15 by mait-elk          #+#    #+#              #
#    Updated: 2024/03/10 10:33:09 by mait-elk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS= -Wall -Werror -Wextra 
CC= cc $(CFLAGS)
INC= include/
SRCS= srcs/utils.c srcs/initializer.c srcs/philos.c
O_SRCS= $(SRCS:.c=.o)
NAME= philo

all: $(NAME)

$(NAME): $(O_SRCS) $(NAME).c $(INC)philo.h
	$(CC) $(NAME).c $(O_SRCS) -o $(NAME) -I $(INC)

srcs/%.o: srcs/%.c $(INC)philo.h
	$(CC) -c $< -o $@ -I $(INC)

clean:
	rm -f $(O_SRCS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean