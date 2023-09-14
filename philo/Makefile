# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 08:58:13 by ncasteln          #+#    #+#              #
#    Updated: 2023/09/14 09:00:47 by ncasteln         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -g -pthread -Wall -Wextra #-Werror #or -lpthread

# ------------------------------------------------------------------------- SRC
SRC = main.c \
	threads.c \
	routines.c \
	time.c \
	create_philo.c \
	create_monastery.c \
	utils.c \
	print_utils.c \
	error.c
VPATH = ./src/
OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER = ./include/philo.h

# ----------------------------------------------------------------------- RULES
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o: %.c $(HEADER)
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I./include/

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
