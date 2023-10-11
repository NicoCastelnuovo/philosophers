# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 08:58:13 by ncasteln          #+#    #+#              #
#    Updated: 2023/10/11 11:05:15 by ncasteln         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -g -pthread -Wall -Wextra #-Werror #or -lpthread
FSANITIZE = -fsanitize=thread

# ------------------------------------------------------------------------- SRC
SRC = main.c \
	threads.c \
	philo_routine.c \
	monitor_routine.c \
	time.c \
	create_philo.c \
	create_monastery.c \
	utils.c \
	print_utils.c \
	heap_utils.c \
	error.c
VPATH = ./src/
OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))
HEADER = ./include/philo.h

# ----------------------------------------------------------------------- RULES
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) successfully compiled."

$(OBJS_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I./include/

fsanitize: $(OBJS)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "objs cleaned."

fclean: clean
	@rm -rf $(NAME)
	@echo "$(NAME) removed."

re: fclean all

.PHONY: all clean fclean re bonus sanitize
