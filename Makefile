# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oroy <oroy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 18:36:54 by oroy              #+#    #+#              #
#    Updated: 2023/08/04 15:29:03 by oroy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************************* VARIABLES ******************************** #

NAME = pipex

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRC = $(wildcard $(LIBFT_SRC_DIR)/*.c)

SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf

MK_C = $(MAKE) -C

# ********************************** RULES *********************************** #

# BASIC #

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

$(LIBFT): $(LIBFT_SRC)
	$(MK_C) $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(MK_C) $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(LIBFT) $(NAME)

re: fclean all

# VALGRIND #

PARAM = infile ls "grep ^M" "wc -c" "wc -l" cat ls outfile

val: $(NAME)
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	./$(NAME) $(PARAM)
