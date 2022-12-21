# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 22:02:51 by shaas             #+#    #+#              #
#    Updated: 2022/12/06 16:18:57 by shaas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

ISDOCKER := $(shell ls -a /)
ifeq ( , $(findstring .dockerenv, $(ISDOCKER)))
	CC = c++
else
	CC = g++
endif

CC_FLAGS = -Wall -Wextra -Werror -std=c++98 -g

DIR_OBJ = obj/

DIR_SRC = src/

SRC := $(shell find $(DIR_SRC) -name "*.cpp")

OBJ := $(patsubst $(DIR_SRC)%.cpp, $(DIR_OBJ)%.o, $(SRC))

INCLUDE := -I./inc/

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@printf $(BLUE)"Linking objects to a binary file\r"$(RESET)
	@$(CC) $(CC_FLAGS) $(INCLUDE) $^ -o $@
	@printf $(SPACE)$(GREEN)"[✓]\n"$(RESET)
	@printf $(GREEN)$(BOLD)"\t\tCOMPLETE!\n\n"$(RESET)
	@printf $(MAGENTA)"\t\tName of executable: "$(RESET)$(BOLD)$(MAGENTA_BG)" $(NAME) "$(RESET)"\n\n"

$(DIR_OBJ)%.o:	$(DIR_SRC)%.cpp
	@mkdir -p $(dir $@)
	@printf $(BLUE)$(BOLD)"\rCompiling: "$(CYAN)"$(notdir $<)\r"
	@$(CC) $(CC_FLAGS) $(INCLUDE) -c $< -o $@
	@printf $(SPACE)$(GREEN)"[✓]\n"$(RESET)

clean:
	@printf $(MAGENTA)"Removing object files...\r"$(RESET)
	@rm -rf $(DIR_OBJ)
	@printf $(SPACE)$(GREEN)"[✓]\n"$(RESET)

fclean: clean
	@printf $(MAGENTA)"Removing binary file...\r"$(RESET)
	@rm -rf $(NAME)
	@printf $(SPACE)$(GREEN)"[✓]\n\n"$(RESET)

re: fclean all

exe:
	./$(NAME)

run: $(NAME) exe

.PHONY: all clean fclean re exe

# **************************************************************************** #
#	TEXT MODIFIERS / FORMATITING CODES										   #
# **************************************************************************** #

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
SPACE =				"\e[50C"