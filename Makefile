# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 18:36:54 by oroy              #+#    #+#              #
#    Updated: 2023/07/27 15:37:28 by oroy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************************* VARIABLES ******************************** #

NAME = pipex

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRC_DIR = $(LIBFT_DIR)/src
LIBFT_SRC = $(wildcard $(LIBFT_SRC_DIR)/*.c)

SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

AR = ar rcs
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

# ********************************** RULES *********************************** #

# BASIC #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

$(LIBFT): $(LIBFT_SRC)
	cd libft && $(MAKE)

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	cd libft && $(MAKE) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(LIBFT) $(NAME)

re: fclean all

# VALGRIND #

PARAM = infile \"cat\" \"grep Make\" \"wc -l\" outfile

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	./$(NAME) $(PARAM)
