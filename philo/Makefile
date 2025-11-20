# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: beatde-a <beatde-a@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 12:39:36 by pedde-so          #+#    #+#              #
#    Updated: 2025/11/13 19:44:08 by beatde-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
SRC_FILES	=	main

INCLUDES	=	philo

OBJ_DIR		=	obj


CC			=	cc -g -O0
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDES) -MMD -MP
RM			=	rm -rf

RED=\033[0;31m
GREEN	    := \033[92;5;118m
ORANGE      := \033[38;5;208m
YELLOW      := \033[38;5;226m
GREEN       := \033[38;5;082m
BLUE        := \033[38;5;027m
INDIGO      := \033[38;5;057m
VIOLET      := \033[38;5;129m
BLINK       := \033[5m
CURSIVE	    := \033[33;3m
DEF_COLOUR=\033[0m

SRC			=	$(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
DEP			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .d, $(SRC_FILES)))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@ctags -R .

$(OBJ_DIR):
	@echo "Compiling philosophers..."
	@mkdir -p $@


clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) tags

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEP)
