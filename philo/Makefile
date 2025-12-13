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
SRC_FILES	=	main parser forks philos actions simulation simulation_utils time\
			threads writes clean safe_checks not_libft really_not_libft

OBJ_DIR		=	obj
SRC_DIR		=	.

INCLUDES	=	-I. 

CC		=	cc -g -O3
CFLAGS		=	-Wall -Wextra -Werror -pthread -fsanitize=thread $(INCLUDES) -MMD -MP
RM		=	rm -rf

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

SRC 		        =	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))
DEP			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .d, $(SRC_FILES)))

.PHONY: all clean fclean re

all: $(NAME)
	@echo "	\n\
		$(RED) _______ _   _ ___          _________ ___ _______ _   _ _____ __________ $(DEF_COLOUR)\n\
		$(ORANGE)(   _   ) | | (   )   /\   / _ \  ___) _ (   _   ) | | |  ___)  _ \  ___)$(DEF_COLOUR)\n\
		$(YELLOW) | | | || |_| || |   /  \ | | | \ \ | | | | | | || |_| | |_  | |_) ) \   $(DEF_COLOUR)\n\
		$(GREEN) | | | ||  _  || |  / /\ \| | | |> >| | | | | | ||  _  |  _) |  __/ > >  $(DEF_COLOUR)\n\
		$(BLUE) | | | || | | || | / /  \ \ |_| / /_| |_| | | | || | | | |___| |   / /__ $(DEF_COLOUR)\n\
		$(INDIGO) |_| |_||_| |_(___)_/    \_\___/_____)___/|_| |_||_| |_|_____)_|  /_____)$(DEF_COLOUR)\n "


$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@ctags -R .

$(OBJ_DIR):
	@echo "Compiling philosophers..."
	@mkdir -p $(OBJ_DIR)


headers: philo.h

clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) tags

fclean: clean
	@$(RM) $(NAME)

re: fclean all

-include $(DEP)
