# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 22:02:51 by shaas             #+#    #+#              #
#    Updated: 2022/11/08 22:35:06 by shaas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

ISDOCKER := $(shell ls -a /)
ifeq ( , $(findstring .dockerenv, $(ISDOCKER)))
	CC = c++
else
	CC = g++
endif

CC_FLAGS = -Wall -Wextra -Werror -std=c++98

DIR_OBJ = obj/

DIR_SRC = prototype_dnc/

SRC := $(wildcard $(DIR_SRC)*.cpp)

OBJ := $(patsubst $(DIR_SRC)%.cpp, $(DIR_OBJ)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CC_FLAGS) $^ -o $@
	@printf $(BLUE)"$(NAME) created\n"$(RESET)

$(DIR_OBJ)%.o:	$(DIR_SRC)%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf "$(notdir $<) compiled\n"

clean:
	@rm -rf $(DIR_OBJ)
	@printf $(RED)"Object files removed\n"$(RESET)

fclean: clean
	@rm -rf $(NAME)
	@printf $(RED)"$(NAME) removed\n"$(RESET)

re: fclean all

exe:
	./$(NAME) $(arg)

run: $(NAME) exe

.PHONY: all clean fclean re exe both

# text modifiers #
RED =				"\e[31m"
GREEN =				"\e[32m"
YELLOW =			"\e[33m"
BLUE =				"\e[34m"
MAGENTA =			"\e[35m"
CYAN =				"\e[36m"
LIGHTGRAY =			"\e[37m"
DARKGRAY =			"\e[90m"
LIGHTRED =			"\e[91m"
LIGHTGREEN =		"\e[92m"
LIGHTYELLOW =		"\e[93m"
LIGHTBLUE =			"\e[94m"
LIGHTMAGENTA =		"\e[95m"
LIGHTCYAN =			"\e[96m"
RED_BG =			"\e[41m"
GREEN_BG =			"\e[42m"
YELLOW_BG =			"\e[43m"
BLUE_BG =			"\e[44m"
MAGENTA_BG =		"\e[45m"
CYAN_BG =			"\e[46m"
LIGHTGRAY_BG =		"\e[47m"
DARKGRAY_BG =		"\e[100m"
LIGHTRED_BG =		"\e[101m"
LIGHTGREEN_BG =		"\e[102m"
LIGHTYELLOW_BG =	"\e[103m"
LIGHTBLUE_BG =		"\e[104m"
LIGHTMAGENTA_BG =	"\e[105m"
LIGHTCYAN_BG =		"\e[106m"
BOLD =				"\e[1m"
ITALIC =			"\e[3m"
UNDERLINED =		"\e[4m"
RESET =				"\e[0m"
