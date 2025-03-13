# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 16:06:17 by mlitvino          #+#    #+#              #
#    Updated: 2025/03/13 12:36:36 by mlitvino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -I$(INCLD_DIR) -pthread -Wall -Wextra -Werror
# -Wall -Wextra -Werror

NAME = philo_bonus

SRC_DIR = ./sources
OBJ_DIR = ./objects
LIBFT_DIR = ./libft
INCLD_DIR = ./includes

SRC = \
		main_bonus.c check_args_bonus.c inits_bonus.c \
		join_clean_bonus.c \
		routine_bonus.c forks_acts_bonus.c \
		utils_bonus.c \
		\
		\
		\
		DEL_bonus.c\
		\
		\
		\
		\

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
INCLD = $(INCLD_DIR)/philo.h_bonus

.SECONDARY: $(OBJ)

all: $(NAME) delete_obj_dir

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) | $(OBJ_DIR)
	$(CC) $(OBJ) -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

delete_obj_dir:
	@if [ -z "$$(ls -A $(OBJ_DIR))" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "make: Nothing to be done for 'all'."; \
	fi

re: fclean all

.PHONY: all clean fclean re delete_obj_dir
